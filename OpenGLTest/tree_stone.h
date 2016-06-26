#pragma once

#include "vector3.h"
#include "vector2.h"


class Tree {

public:
	Tree ();
	Tree (Vector2 Position, real Tsize);
	~Tree ();

private:
	const real TRadius = 1.0;
	const real Height = 4.0;

public:
	Vector2 TPosition;
	real size;
	static Tree FindTree (int intChunk);

};

class Stone {

public:
	Stone ();
	Stone (Vector3 Position, real Ssize);
	~Stone ();

private:
	const real SRadius = 1.0;
	const real Height = 1.0;

public:
	Vector3 SPosition;
	real size;
	static Stone FindStone (int intChunk);

};

