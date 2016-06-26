#pragma once

#include <GL/freeglut.h>

class Sky {

public:
	Sky ();
	//��ʼ����յ�λ�ã��뾶������
	void InitSky (float skyX, float skyY, float skyZ, float skyR, unsigned int texture);

	//��ʾ���
	void ShowSky ();

	//�����յ�����
	float GetSkyX (void);
	float GetSkyY (void);
	float GetSkyZ (void);
	float GetSkyR (void);
	unsigned int GetSkyTexture (void);

private:
	float X;
	float Y;
	float Z;
	float R;
	unsigned int T;
	GLUquadricObj *qobj;
};

