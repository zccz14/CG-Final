#include "vector2.h"
real Vector2::distance22(Vector2 A, Vector2 B) {
	return (A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y);
}

real Vector2::length2(Vector2 A) {
	return (A.x*A.x + A.y*A.y);
}

Vector2 Vector2::minusVector2(Vector2 A, Vector2 B) {
	Vector2 C;
	C.x = A.x - B.x;
	C.y = A.y - B.y;
	return C;
}

Vector2 Vector2::decoVector2(Vector2 A, Vector2 B) {
	Vector2 C;
	real a;
	a = (A.x*B.x + A.y*B.y) / (B.x*B.x + B.y*B.y);//cos<A,B>
	C.x = A.x - a*B.x;
	C.y = A.y - a*B.y;
	return C;
}

Vector2 Vector2::unitVector2(Vector2 A) {
	real a;
	a = real_sqrt(Vector2::length2(A));
	A.x /= a;
	A.y /= a;
	return A;
}

Vector2 Vector2::kVector2(real k, Vector2 A) {
	Vector2 B;
	B.x = k*A.x;
	B.y = k*A.y;
	return B;
}

//Vector3 Vector2::addAcceleration(Vector2 A, real g) {
//	Vector3 Acceleration;
//	Acceleration.x = A.x;
//	Acceleration.y = A.y;
//	Acceleration.z = g;
//	return Acceleration;
//}