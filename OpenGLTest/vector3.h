#pragma once
#include "name.h"
class Vector3 {
public:
	real x;
	real y;
	real z;

public:
	Vector3(real x, real y, real z);
	Vector3();
	static Vector3 add(Vector3 A, Vector3 B);
	static Vector3 minus(Vector3 A, Vector3 B);
	real module(Vector3 A);
	static real dotProduct(Vector3 A, Vector3 B);
	static Vector3 crossProduct(Vector3 A, Vector3 B);

	static Vector3 addVector3(Vector3 A, Vector3 B);
	static Vector3 minusVector3(Vector3 A, Vector3 B);
	static real lengthVector32(Vector3 A);
	static real dotpVector3(Vector3 A, Vector3 B);
	static Vector3 crosspVector3(Vector3 A, Vector3 B);
	static Vector3 decoVector3(Vector3 A, Vector3 B);
	static Vector3 kVector3(real k, Vector3 A);
	static real distance32(Vector3 A, Vector3 B);
};
