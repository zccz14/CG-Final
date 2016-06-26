#pragma once
#include "name.h"
#include "vector3.h"
class Chunk {
public:
	int x;
	int y;

public:
	static int intChunkGet(Vector3 Position);

};

class Vector2 {
public:
	real x;
	real y;

public:
	static real distance22(Vector2 A, Vector2 B);
	static real length2(Vector2 A);
	static Vector2 minusVector2(Vector2 A, Vector2 B);
	static Vector2 decoVector2(Vector2 A, Vector2 B);
	static Vector2 unitVector2(Vector2 A);
	static Vector2 kVector2(real k, Vector2 A);
	static Vector3 addAcceleration(Vector2 F, real g);
};
