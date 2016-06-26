#pragma once
#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>  
#include <cstdio> 
#include <windows.h>
#include "Sky.h"

using std::cout;
using std::cin;
using std::endl;
const int BITMAP_ID = 0x4D42;
GLuint texture[3];
Sky sky;

//������ͼƬ  
unsigned char *LoadBitmapFile (char *filename, BITMAPINFOHEADER *bitmapInfoHeader) {
	FILE *filePtr;    // �ļ�ָ��  
	BITMAPFILEHEADER bitmapFileHeader;    // bitmap�ļ�ͷ  
	unsigned char    *bitmapImage;        // bitmapͼ������  
	int    imageIdx = 0;        // ͼ��λ������  
	unsigned char    tempRGB;    // ��������  

								 // �ԡ�������+����ģʽ���ļ�filename   
	fopen_s (&filePtr, filename, "rb");
	if (filePtr == NULL) {
		printf ("file not open\n");
		return NULL;
	}
	// ����bitmap�ļ�ͼ  
	fread (&bitmapFileHeader, sizeof (BITMAPFILEHEADER), 1, filePtr);
	// ��֤�Ƿ�Ϊbitmap�ļ�  
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf (stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}
	// ����bitmap��Ϣͷ  
	fread (bitmapInfoHeader, sizeof (BITMAPINFOHEADER), 1, filePtr);
	// ���ļ�ָ������bitmap����  
	fseek (filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	if (bitmapInfoHeader->biSizeImage <= 0) {
		bitmapInfoHeader->biSizeImage = 62500;
	}
	// Ϊװ��ͼ�����ݴ����㹻���ڴ�  
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// ��֤�ڴ��Ƿ񴴽��ɹ�  
	if (!bitmapImage) {
		fprintf (stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// ����bitmapͼ������  
	fread (bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// ȷ�϶���ɹ�  
	if (bitmapImage == NULL) {
		fprintf (stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	//����bitmap�б���ĸ�ʽ��BGR�����潻��R��B��ֵ���õ�RGB��ʽ  
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// �ر�bitmapͼ���ļ�  
	fclose (filePtr);
	return bitmapImage;
}

//��������ĺ���  
void texload (int i, char *filename) {
	BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap��Ϣͷ  
	unsigned char*   bitmapData;                                       // ��������  

	bitmapData = LoadBitmapFile (filename, &bitmapInfoHeader);
	if (i == 0) {
		glBindTexture (GL_TEXTURE_2D, texture[0]);
		sky.InitSky (25, 25, 0, 100, texture[0]);
	} else {
		glBindTexture (GL_TEXTURE_2D, texture[i]);
	}
	// ָ����ǰ����ķŴ�/��С���˷�ʽ  
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	cout << "bitmapInfoHeader.biWidth" << bitmapInfoHeader.biWidth << endl;
	cout << "bitmapInfoHeader.biHeight" << bitmapInfoHeader.biHeight << endl;
	glTexImage2D (GL_TEXTURE_2D,
		0,         //mipmap���(ͨ��Ϊ����ʾ���ϲ�)   
		GL_RGB,    //����ϣ���������к졢�̡�������  
		bitmapInfoHeader.biWidth, //��������������n�����б߿�+2   
		-bitmapInfoHeader.biHeight, //����߶ȣ�������n�����б߿�+2   
		0, //�߿�(0=�ޱ߿�, 1=�б߿�)   
		GL_RGB,    //bitmap���ݵĸ�ʽ  
		GL_UNSIGNED_BYTE, //ÿ����ɫ���ݵ�����  
		bitmapData);    //bitmap����ָ��    
}

//��������ĺ���  
void TextureInit () {
	glGenTextures (2, texture); // ��һ��������Ҫ���ɱ�ʾ���ĸ���, �ڶ������Ƿ��ر�ʾ��������  
	texload (0, "sky.bmp");
	texload (1, "water.bmp");

}
