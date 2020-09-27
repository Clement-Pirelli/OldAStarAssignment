#pragma once
#include <vector>
#include "structs.h"

class Grid;

struct Node
{
	int f = {0};
	int g = {0};
	int h = {0};
	vector2DInt pos = {};

	Node() = default;
	Node(int givenF, int givenG, int givenH, vector2DInt givenpos){ f = givenF; g = givenG; h = givenH; pos = givenpos; };
};

class Astarrer
{
public:
	static std::vector<vector2DInt> findPath(const vector2DInt &start, const vector2DInt &destination, const Grid &grid);
};