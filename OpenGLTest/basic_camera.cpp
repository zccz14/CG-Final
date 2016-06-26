#include <GL\freeglut.h>
#include "basic_camera.h"
#include "main.h"



BasicCamera::BasicCamera(GLfloat eye[3], GLfloat center[3], GLfloat up[3]) {
	BasicCamera(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
}

BasicCamera::BasicCamera(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy, GLfloat upz) {
	this->eye[0] = eyex;
	this->eye[1] = eyey;
	this->eye[2] = eyez;
	this->center[0] = centerx;
	this->center[1] = centery;
	this->center[2] = centerz;
	this->up[0] = upx;
	this->up[1] = upy;
	this->up[2] = upz;
}

void BasicCamera::see() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45, whRatio, 0.1, 100);
	gluLookAt(
		this->eye[0], this->eye[1], this->eye[2],
		this->center[0], this->center[1], this->center[2],
		this->up[0], this->up[1], this->up[2]
		);
	//glMatrixMode(GL_MODELVIEW);
}

void BasicCamera::setShape(int w, int h) {
	this->width = w;
	this->height = h;
	this->whRatio = GLfloat(w) / h;
}

void BasicCamera::move(GLfloat x, GLfloat y, GLfloat z) {
	this->eye[0] = x;
	this->eye[1] = y;
	this->eye[2] = z;
}