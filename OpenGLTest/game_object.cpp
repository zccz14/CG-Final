#include "game_object.h"
GameObject::GameObject() {
	this->position = Vector3(0, 0, 0);
	this->rotation = Vector3(0, 0, 0);
	this->scale = Vector3(1, 1, 1);
}

Vector3 GameObject::getPosition() {
	return Vector3(this->position);
}

Vector3 GameObject::getRotation() {
	return Vector3(this->rotation);
}

Vector3 GameObject::getScale() {
	return Vector3(this->scale);
}
GameObject GameObject::setPosition(GLfloat x, GLfloat y, GLfloat z) {
	this->position = Vector3(x, y, z);
	return *this;
}

GameObject GameObject::setRotation(GLfloat x, GLfloat y, GLfloat z) {
	this->rotation = Vector3(x, y, z);
	return *this;
}

GameObject GameObject::setScale(GLfloat x, GLfloat y, GLfloat z) {
	this->scale = Vector3(x, y, z);
	return *this;
}

GameObject GameObject::move(GLfloat x, GLfloat y, GLfloat z) {
	this->position.x += x;
	this->position.y += y;
	this->position.z += z;
	return *this;
}

GameObject GameObject::rotate(GLfloat x, GLfloat y, GLfloat z) {
	this->rotation.x += x;
	this->rotation.y += y;
	this->rotation.z += z;
	return *this;
}

GameObject GameObject::zoom(GLfloat x, GLfloat y, GLfloat z) {
	this->zoom.x += x;
	this->zoom.y += y;
	this->zoom.z += z;
	return *this;
}
