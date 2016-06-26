#pragma once
#include "basic_camera.h"
class FPSCamera : public BasicCamera {
public:
	FPSCamera(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy, GLfloat upz);
	FPSCamera(GLfloat eye[3], GLfloat center[3], GLfloat up[3]);
};