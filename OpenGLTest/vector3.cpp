#include "vector3.h"
#include "vector2.h"

Vector3::Vector3(real x, real y, real z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3() {
	Vector3(0, 0, 0);
}

Vector3 Vector3::addVector3(Vector3 A, Vector3 B) {
	Vector3 C;
	C.x = A.x + B.x;
	C.y = A.y + B.y;
	C.z = A.z + B.z;
	return C;
}//�����ӷ�

Vector3 Vector3::minusVector3(Vector3 A, Vector3 B) {
	Vector3 C;
	C.x = A.x - B.x;
	C.y = A.y - B.y;
	C.z = A.z - B.z;
	return C;
}//��������

real Vector3::lengthVector32(Vector3 A) {
	return A.x*A.x + A.y*A.y + A.z*A.z;
}//����ƽ��

real Vector3::dotpVector3(Vector3 A, Vector3 B) {
	real a;
	a = A.x*B.x + A.y*B.y + A.z*B.z;
	return a;
}//���

Vector3 Vector3::crosspVector3(Vector3 A, Vector3 B) {
	Vector3 C;
	C.x = A.y*B.z - A.z*B.y;
	C.y = A.z*B.x - A.x*B.z;
	C.z = A.x*B.y - A.y*B.x;
	return C;
}//���

Vector3 Vector3::decoVector3(Vector3 A, Vector3 B) {
	Vector3 C;
	real a;
	a = (A.x*B.x + A.y*B.y + A.z*B.z) / (B.x*B.x + B.y*B.y + B.z*B.z);//cos<A,B>
	C.x = A.x - a*B.x;
	C.y = A.y - a*B.y;
	C.z = A.z - a*B.z;
	return C;
}//����A����BΪ��������ƽ���ϵ�ͶӰ

Vector3 Vector3::kVector3(real k, Vector3 A) {
	Vector3 B;
	B.x = k*A.x;
	B.y = k*A.y;
	B.z = k*A.z;
	return B;
}

real Vector3::distance32(Vector3 A, Vector3 B) {
	return Vector3::lengthVector32(Vector3::minusVector3(A, B));
}

Vector3 Vector2::addAcceleration (Vector2 A, real g) {
	Vector3 Acceleration;
	Acceleration.x = A.x;
	Acceleration.y = A.y;
	Acceleration.z = g;
	return Acceleration;
}