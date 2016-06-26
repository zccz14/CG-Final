#pragma once
#include "vector3.h"
#include "game_object.h"
class Rigidbody : public GameObject {
private:
	real inversedMass;
	bool isUseGravity;
public:
	Rigidbody();
	
};