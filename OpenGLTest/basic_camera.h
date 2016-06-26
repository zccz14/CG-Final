#pragma once
#include <GL\freeglut.h>
class BasicCamera {
private:
	GLfloat eye[3], center[3], up[3];
	int width, height;
	GLfloat whRatio;
public:
	BasicCamera(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy, GLfloat upz);
	BasicCamera(GLfloat eye[3], GLfloat center[3], GLfloat up[3]);
	void setShape(int width, int height);
	void move(GLfloat x, GLfloat y, GLfloat z);
	void lookAt(GLfloat x, GLfloat y);
	void see();
};