#include "Grid.h"
#include "EntityManager.h"

EntityManager::EntityManager()
{

	SPACESHIP_REC = { vector2D{Grid::CELL_DIMENSIONS.x*.6f, Grid::CELL_DIMENSIONS.y*.6f}, color{.0f, .0f, 1.0f}, 0.1f };
	TRADER_REC = { vector2D{Grid::CELL_DIMENSIONS.x*.7f, Grid::CELL_DIMENSIONS.y*.4f}, color{1.0f, 1.0f, 1.0f}, 0.1f };
	STAR_REC = { vector2D{Grid::CELL_DIMENSIONS.x*.3f, Grid::CELL_DIMENSIONS.y*.3f}, color{1.0f, 1.0f, .0f}, 0.1f };

	//the ship's position is a random tile
	vector2DInt shipPosition = { rand() % Grid::GRID_SIZE.x, rand() % Grid::GRID_SIZE.y };
	spaceship = new Entity(SPACESHIP_REC, Grid::gridToPixel(shipPosition), shipPosition);

	//the trader's position is also a random tile
	vector2DInt traderPosition = { rand() % Grid::GRID_SIZE.x, rand() % Grid::GRID_SIZE.y };
	//the trader and the ship shouldn't be on the same tile
	for (int i = 0; i < 10; i++)
	{
		if (traderPosition == shipPosition)
			traderPosition = { rand() % Grid::GRID_SIZE.x, rand() % Grid::GRID_SIZE.y };
		else
			break;
	}
	trader = new Entity(TRADER_REC, Grid::gridToPixel(traderPosition), traderPosition);
}

EntityManager::~EntityManager()
{
	if(star != nullptr)
		delete star;
	delete spaceship;
	delete trader;
}

void EntityManager::tick(float deltatime)
{
	//the current entities don't need to be updated
}

void EntityManager::draw()
{
	spaceship->draw();
	trader->draw();
	if (star != nullptr) star->draw();
}


vector2DInt EntityManager::getSpaceshipGridPos()
{
	return spaceship->getGridPos();
}

vector2DInt EntityManager::getTraderGridPos()
{
	return trader->getGridPos();
}

Entity *EntityManager::getStar()
{
	return star;
}

void EntityManager::setSpaceshipGridPos(vector2DInt pos)
{
	spaceship->setGridPos(pos);
}

void EntityManager::setTraderGridPos(vector2DInt pos)
{
	trader->setGridPos(pos);
}

void EntityManager::addStar(vector2DInt pos)
{
	//delete the already existing star if it exists
	if (star != nullptr) delete star;

	star = new Entity(STAR_REC, Grid::gridToPixel(pos), pos);
}

bool EntityManager::removeStar(vector2DInt pos)
{
	if (star == nullptr) return false;

	if(star->getGridPos() == pos)
	{
		delete star;
		star = nullptr;
		return true;
	}
}
