#pragma once

#include <GL/freeglut.h>

class Sky {

public:
	Sky ();
	//初始化天空的位置，半径和纹理
	void InitSky (float skyX, float skyY, float skyZ, float skyR, unsigned int texture);

	//显示天空
	void ShowSky ();

	//获得天空的属性
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

