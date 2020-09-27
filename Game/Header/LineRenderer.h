#pragma once 
#include "structs.h"
#include <vector>

class LineRenderer
{
public:
	LineRenderer(std::vector<vector2D> givenPoints, color givenCol, float givenDepth);

	void draw() const;
	void setPoints(std::vector<vector2D> givenPoints){ points = givenPoints; };
	void popPointsFront(){ points.erase(points.begin()); };
private:
	std::vector<vector2D> points;
	float depth;
	color col;
};