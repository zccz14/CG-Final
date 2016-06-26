#include "tree_stone.h"

	Tree::Tree () {
		TPosition.x = 0.0;
		TPosition.y = 0.0;
		size = 0.0;
		Height;
		TRadius;
	}

	Tree::Tree (Vector2 Position, real Tsize) {
		TPosition.x = Position.x;
		TPosition.y = Position.y;
		size = Tsize;
		Height;
		TRadius;
	}

	Stone Stone12, Stone24, Stone31, Stone41;
	Tree Tree23, Tree32, Tree43, Tree54;

	Tree Tree::FindTree (int intChunk) {
		switch (intChunk) {
		case '32':
			return Tree32;
			break;
		case '43':
			return Tree43;
			break;
		case '54':
			return Tree54;
			break;
		}
	}

	Tree::~Tree () {

	}


	Stone::Stone () {
		SPosition.x = 0.0;
		SPosition.y = 0.0;
		SPosition.z = 0.0;
		size = 0.0;
	}

	Stone::Stone (Vector3 Position, real Ssize) {
		SPosition.x = Position.x;
		SPosition.y = Position.y;
		SPosition.z = Position.z;
		size = Ssize;
		SRadius;
	}

	Stone Stone::FindStone (int intChunk) {
		switch (intChunk) {
		case '12':
			return Stone12;
			break;
		case '24':
			return Stone24;
			break;
		case '31':
			return Stone31;
			break;
		case '41':
			return Stone41;
			break;
		}
	}

	Stone::~Stone () {

	}
