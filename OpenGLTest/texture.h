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

//读纹理图片  
unsigned char *LoadBitmapFile (char *filename, BITMAPINFOHEADER *bitmapInfoHeader) {
	FILE *filePtr;    // 文件指针  
	BITMAPFILEHEADER bitmapFileHeader;    // bitmap文件头  
	unsigned char    *bitmapImage;        // bitmap图像数据  
	int    imageIdx = 0;        // 图像位置索引  
	unsigned char    tempRGB;    // 交换变量  

								 // 以“二进制+读”模式打开文件filename   
	fopen_s (&filePtr, filename, "rb");
	if (filePtr == NULL) {
		printf ("file not open\n");
		return NULL;
	}
	// 读入bitmap文件图  
	fread (&bitmapFileHeader, sizeof (BITMAPFILEHEADER), 1, filePtr);
	// 验证是否为bitmap文件  
	if (bitmapFileHeader.bfType != BITMAP_ID) {
		fprintf (stderr, "Error in LoadBitmapFile: the file is not a bitmap file\n");
		return NULL;
	}
	// 读入bitmap信息头  
	fread (bitmapInfoHeader, sizeof (BITMAPINFOHEADER), 1, filePtr);
	// 将文件指针移至bitmap数据  
	fseek (filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);
	if (bitmapInfoHeader->biSizeImage <= 0) {
		bitmapInfoHeader->biSizeImage = 62500;
	}
	// 为装载图像数据创建足够的内存  
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];
	// 验证内存是否创建成功  
	if (!bitmapImage) {
		fprintf (stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}

	// 读入bitmap图像数据  
	fread (bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);
	// 确认读入成功  
	if (bitmapImage == NULL) {
		fprintf (stderr, "Error in LoadBitmapFile: memory error\n");
		return NULL;
	}
	//由于bitmap中保存的格式是BGR，下面交换R和B的值，得到RGB格式  
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3) {
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}
	// 关闭bitmap图像文件  
	fclose (filePtr);
	return bitmapImage;
}

//加载纹理的函数  
void texload (int i, char *filename) {
	BITMAPINFOHEADER bitmapInfoHeader;                                 // bitmap信息头  
	unsigned char*   bitmapData;                                       // 纹理数据  

	bitmapData = LoadBitmapFile (filename, &bitmapInfoHeader);
	if (i == 0) {
		glBindTexture (GL_TEXTURE_2D, texture[0]);
		sky.InitSky (25, 25, 0, 100, texture[0]);
	} else {
		glBindTexture (GL_TEXTURE_2D, texture[i]);
	}
	// 指定当前纹理的放大/缩小过滤方式  
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	cout << "bitmapInfoHeader.biWidth" << bitmapInfoHeader.biWidth << endl;
	cout << "bitmapInfoHeader.biHeight" << bitmapInfoHeader.biHeight << endl;
	glTexImage2D (GL_TEXTURE_2D,
		0,         //mipmap层次(通常为，表示最上层)   
		GL_RGB,    //我们希望该纹理有红、绿、蓝数据  
		bitmapInfoHeader.biWidth, //纹理宽带，必须是n，若有边框+2   
		-bitmapInfoHeader.biHeight, //纹理高度，必须是n，若有边框+2   
		0, //边框(0=无边框, 1=有边框)   
		GL_RGB,    //bitmap数据的格式  
		GL_UNSIGNED_BYTE, //每个颜色数据的类型  
		bitmapData);    //bitmap数据指针    
}

//定义纹理的函数  
void TextureInit () {
	glGenTextures (2, texture); // 第一参数是需要生成标示符的个数, 第二参数是返回标示符的数组  
	texload (0, "sky.bmp");
	texload (1, "water.bmp");

}
