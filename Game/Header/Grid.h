#pragma once

#ifndef GRID_H_DEFINED
#define GRID_H_DEFINED

#include "structs.h"
#include "RecDrawer.h"

struct Cell : public RecDrawer
{
	Cell() : RecDrawer(recData{}, vector2D{ 0.0f, 0.0f }){};
	~Cell(){};

	enum CELL_TYPE
	{
		MOUNTAIN,
		GRASS,
		IMPASSABLE
	};

	void setTypeData(recData givenRec, CELL_TYPE givenType);

	static constexpr int GRASS_COST = 1;
	static constexpr int MOUNTAIN_COST = 3;

	vector2DInt gridPos = {};
	CELL_TYPE type = {};
};

class Grid
{
public:
	Grid();
	~Grid();

	static const vector2DInt GRID_SIZE;
	static const vector2D CELL_DIMENSIONS;

	void draw() const;
	void tick(float deltaTime);

	static vector2D gridToPixel(vector2DInt coordinates);
	static vector2DInt pixelToGrid(vector2D coordinates);
	Cell *getCell(vector2DInt coordinates) const;
	Cell *getCell(vector2D coordinates) const;
	void setCellType(Cell::CELL_TYPE givenType, vector2DInt coordinates);

	static const recData MOUNTAIN_REC;
	static const recData GRASS_REC;
	static const recData IMPASSABLE_REC;

private:

	Cell *terrain;

	static const vector2D origo;
};

#endif