#include "Grid.h"
#include "Entity.h"


//GRID FUNCTIONS
const vector2DInt Grid::GRID_SIZE = { 32, 32 };
const vector2D Grid::CELL_DIMENSIONS = { 2.0f / (float)GRID_SIZE.x, 2.0f / (float)GRID_SIZE.y };
const recData Grid::MOUNTAIN_REC = { vector2D{CELL_DIMENSIONS.x*.5f, CELL_DIMENSIONS.y*.5f}, color{.6f, .6f, .6f}, 0.2f  };
const recData Grid::GRASS_REC = { vector2D{CELL_DIMENSIONS.x*.5f, CELL_DIMENSIONS.y*.5f}, color{.0f, 1.0f, .0f}, 0.2f };
const recData Grid::IMPASSABLE_REC = { vector2D{CELL_DIMENSIONS.x*.5f, CELL_DIMENSIONS.y*.5f}, color{.0f, .0f, .0f}, 0.2f };
const vector2D Grid::origo = { -1.0f + CELL_DIMENSIONS.x / 2.0f, -1.0f + CELL_DIMENSIONS.y / 2.0f };

Grid::Grid()
{
	terrain = new Cell[GRID_SIZE.x * GRID_SIZE.y];	

	for (int i = 0; i < GRID_SIZE.x * GRID_SIZE.y; i++)
	{
		terrain[i].gridPos = vector2DInt{ i % GRID_SIZE.y, i / GRID_SIZE.x };
		terrain[i].setPos(gridToPixel(terrain[i].gridPos));

		terrain[i].setTypeData(GRASS_REC, Cell::GRASS);

		float random = (float)rand() / (float)RAND_MAX;
		if(random > 0.8f) terrain[i].setTypeData(MOUNTAIN_REC, Cell::MOUNTAIN);
		if (random < 0.2f) terrain[i].setTypeData(IMPASSABLE_REC, Cell::IMPASSABLE);
		
	}
}

Grid::~Grid()
{
	delete[] terrain;
}

void Grid::tick(float deltatime)
{
}

void Grid::draw() const
{
	for (int i = 0; i < GRID_SIZE.x * GRID_SIZE.y; i++)
	{
		terrain[i].draw();
	}
}

vector2D Grid::gridToPixel(vector2DInt coordinates)
{
	return vector2D{ origo.x + coordinates.x * CELL_DIMENSIONS.x, origo.y + coordinates.y * CELL_DIMENSIONS.y};
}

vector2DInt Grid::pixelToGrid(vector2D coordinates)
{
	return vector2DInt{ (int)((coordinates.x+1.0f) / CELL_DIMENSIONS.x), (int)(GRID_SIZE.y - ((coordinates.y+1.0f) / CELL_DIMENSIONS.y))};
}

Cell *Grid::getCell(vector2DInt coordinates) const
{
	//if the cell is out of bound, fail
	if( coordinates.x >= GRID_SIZE.x || coordinates.y >= GRID_SIZE.y ||
		coordinates.x < 0 || coordinates.y < 0) return nullptr;

	return &terrain[coordinates.y * GRID_SIZE.y + coordinates.x] ;
}

Cell* Grid::getCell(vector2D coordinates) const
{
	vector2DInt cellPos = pixelToGrid(coordinates);
	return getCell(cellPos);
}

void Grid::setCellType(Cell::CELL_TYPE givenType, vector2DInt coordinates)
{
	Cell* selectedCell = getCell(coordinates);
	if (selectedCell == nullptr) return;
	switch(givenType)
	{
	case Cell::CELL_TYPE::GRASS:
		selectedCell->setTypeData(GRASS_REC, Cell::CELL_TYPE::GRASS);
		break;
	case Cell::CELL_TYPE::MOUNTAIN:
		selectedCell->setTypeData(MOUNTAIN_REC, Cell::CELL_TYPE::MOUNTAIN);
		break;
	case Cell::CELL_TYPE::IMPASSABLE:
		selectedCell->setTypeData(IMPASSABLE_REC, Cell::CELL_TYPE::IMPASSABLE);
		break;
	}
}



//CELL FUNCTIONS

void Cell::setTypeData(recData givenRec, CELL_TYPE givenType)
{
	setRec(givenRec);
	type = givenType;
}
