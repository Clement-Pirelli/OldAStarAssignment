#pragma once



#ifndef STRUCTS_H_DEFINED
#define STRUCTS_H_DEFINED

#define GL_GLEXT_PROTOTYPES

#include <stdlib.h>
#include "glut.h"
#include <math.h>
#include <utility>

struct color
{
	float r;
	float g;
	float b;
};

enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	COUNT
};

union vector2D
{
	struct
	{
		float x;
		float y;
	};

	struct 
	{
		float w;
		float h;
	};

	static const float getMagnitude(vector2D a)
	{
		return sqrtf
		(
			powf(a.x, 2.0f) + powf(a.y, 2.0f)
		);
	}

	static vector2D normalize(vector2D a)
	{
		a /= vector2D::getMagnitude(a);
		return a;
	}

	vector2D operator + (vector2D a){ return vector2D{ x + a.x, y + a.y }; }
	vector2D operator - (vector2D a){ return vector2D{ x - a.x, y - a.y }; }
	void operator -= (float a){ x -= a; y -= a; };
	void operator /= (float a){ x /= a; y /= a; };
	void operator *= (float a){ x *= a; y *= a; };
};

struct vector2DInt
{
	int x;
	int y;

	static vector2DInt getDirectionVector(DIRECTION directionEnum)
	{
		vector2DInt dir{ 0, 0 };
		switch (directionEnum){
		case DIRECTION::UP:
			dir.y++;
			break;
		case DIRECTION::DOWN:
			dir.y--;
			break;
		case DIRECTION::LEFT:
			dir.x--;
			break;
		case DIRECTION::RIGHT:
			dir.x++;
			break;
		}
		return dir;
	}

	static vector2DInt getGridDirection(vector2DInt direction)
	{
		vector2DInt n = { 0, 0 };

		if (direction.x == 0 && direction.y == 0) return n;

		if (direction.x > 0) n.x = 1;
		if (direction.x < 0) n.x = -1;

		if (direction.y > 0) n.y = 1;
		if (direction.y < 0)n.y = -1;

		return n;
	}

	static vector2DInt getGridDirection(vector2D direction)
	{
		vector2DInt n = { 0, 0 };

		if (direction.x == .0f && direction.y == .0f) return n;

		if (direction.x > .0f) n.x = 1;
		if (direction.x < .0f) n.x = -1;

		if (direction.y > .0f) n.y = 1;
		if (direction.y < .0f) n.y = -1;

		return n;
	}

	static const float getMagnitude(vector2DInt a)
	{
		return sqrtf
		(
			powf((float)a.x, 2.0f) + powf((float)a.y, 2.0f)
		);
	}

	static const float getDistance(vector2DInt head, vector2DInt tail)
	{
		return sqrtf
		(
			powf((float)head.x - (float)tail.x, 2.0f) + powf((float)head.x - (float)tail.x, 2.0f)
		);
	}


	vector2DInt operator + (vector2DInt a) const { return vector2DInt{ x + a.x, y + a.y }; }
	vector2DInt operator - (vector2DInt a) const { return vector2DInt{ x - a.x, y - a.y }; }
	bool operator == (const vector2DInt &a) const { return (x == a.x && y == a.y); }
	vector2DInt operator *= (int a){ return vector2DInt{ x*a, y*a }; }
};

namespace std {

	template <>
	struct hash<vector2DInt>
	{
		std::size_t operator()(const vector2DInt &k) const
		{
			return ((std::hash<int>()(k.x)
				^ (std::hash<int>()(k.y) << 1)) >> 1);
		}
	};

}

#endif