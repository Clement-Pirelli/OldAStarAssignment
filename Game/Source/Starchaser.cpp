#include "Starchaser.h"
#include "Grid.h"
#include "ChaserStates.h"
#include "EntityManager.h"

Starchaser::Starchaser(recData givenRec, vector2D givenPos, vector2DInt givenGridPos, const Grid& givenGrid, EntityManager &givenEntityManager) : 
	Entity(givenRec, givenPos, givenGridPos), 
	grid(givenGrid), 
	entityManager(givenEntityManager)
{
	ChaserState_Collecting *firstState = new ChaserState_Collecting(this, &stateMachine);

	stateMachine.setFirstState(firstState);
}

Starchaser::~Starchaser(){}

void Starchaser::tick(float deltaTime)
{
	stateMachine.tick(deltaTime);
}

bool Starchaser::getPathTo(vector2DInt destination)
{
	path = findPath(gridPos, destination, grid);

	std::vector<vector2D> linePoints;
	for (size_t i = 0; i < path.size(); i++)
	{
		linePoints.push_back(grid.gridToPixel(path.at(i)));
	}

	lineRenderer.setPoints(linePoints);

	return path.size() > 0;
}

void Starchaser::draw() const
{
	Entity::draw();
	lineRenderer.draw();
}

bool Starchaser::moveThroughPath()
{
	//if we're already at the destination, return
	if (path.size() == 0) return false;
	//get the cell we want to traverse
	Cell *CellToTraverse = grid.getCell(path.front());
	//if the cell we want to traverse is impassable (because the user has changed the terrain
	if (CellToTraverse->type == Cell::CELL_TYPE::IMPASSABLE)
	{
		//clear the path since it's invalid
		path.clear(); 
		//clear the line renderer's points
		lineRenderer.setPoints(std::vector<vector2D>());
		//return
		return false; 
	}
	//otherwise, move to the cell
	gridPos = CellToTraverse->gridPos;
	rectDrawer.setPos(grid.gridToPixel(gridPos));

	//remove the point we just went to, since it's now our current position
	lineRenderer.popPointsFront();
	path.erase(path.begin());

	incrementFatigue(fatigueIncrement);

	//moving was a success
	return true;
}

vector2DInt Starchaser::findStar()
{
	Entity *star = entityManager.getStar();
	//return an invalid value if there's no star
	if (star == nullptr) return vector2DInt{ -1, -1 };
	return star->getGridPos();
}

bool Starchaser::pickupStar()
{
	return entityManager.removeStar(findStar());
}

vector2DInt Starchaser::findTrader()
{
	return entityManager.getTraderGridPos();
}

vector2DInt Starchaser::findShip()
{
	return entityManager.getSpaceshipGridPos();
}