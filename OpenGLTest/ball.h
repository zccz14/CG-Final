#pragma once
#include "vector3.h"
#include "vector2.h"
class Ball {

public:
	Ball();
	Ball(Vector3 BPosition, Vector3 BVelocity);
	~Ball();

public:
	Vector3 Position;
	Vector3 Velocity;
	Vector2 FrictionA;
	real GravitationalA;
	Vector3 Acceleration;
	const real Radius = 0.5;

public:
	bool IscollisionT(Vector2 TPosition, Vector3 Position, real TSize);
	bool IscollisionS(Vector3 SPosition, Vector3 Position, real SSize);
	bool IscollisionWall(Vector3 Position);
	bool IscollisionWater(Vector3 Position);
	int collisionGround(Vector3 Position, Vector3 Velocity);
	Vector3 colTVelocity(Vector2 TPosition, Vector3 Position, real TSize, Vector3 Velocity);
	Vector3 colSVelocity(Vector3 SPosition, Vector3 Position, Vector3 Velocity);
	Vector3 colWVelocity(Vector3 Position, Vector3 Velocity);
	Vector3 colGVelocity(Vector3 Velocity);
	void updateBall(Ball Ball1);

};