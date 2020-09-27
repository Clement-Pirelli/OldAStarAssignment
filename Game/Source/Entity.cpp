#include "Entity.h"
#include "Grid.h"

Entity::Entity(recData givenRec, vector2D givenPos, vector2DInt givenGridPos) : rectDrawer(givenRec, givenPos), gridPos(givenGridPos)
{
}

void Entity::setGridPos(vector2DInt pos)
{
	gridPos = pos;
	rectDrawer.setPos(Grid::gridToPixel(gridPos));
}