#pragma once
#include <GL\freeglut.h>
#include "vector3.h"
class GameObject {
private:
	Vector3 position, rotation, scale;
public:
	GameObject();
	Vector3 getPosition();
	Vector3 getRotation();
	Vector3 getScale();
	GameObject setPosition(GLfloat x, GLfloat y, GLfloat z);
	GameObject setRotation(GLfloat x, GLfloat y, GLfloat z);
	GameObject setScale(GLfloat x, GLfloat y, GLfloat z);
	GameObject move(GLfloat x, GLfloat y, GLfloat z);
	GameObject rotate(GLfloat x, GLfloat y, GLfloat z);
	GameObject zoom(GLfloat x, GLfloat y, GLfloat z);
	GameObject setPosition(Vector3 v);
	GameObject setRotation(Vector3 v);
	GameObject setScale(Vector3 v);
	GameObject move(Vector3 v);
	GameObject rotate(Vector3 v);
	GameObject zoom(Vector3 v);
	virtual void reder();
};