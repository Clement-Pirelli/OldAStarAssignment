#pragma once

#ifndef ENTITY_H_DEFINED
#define ENTITY_H_DEFINED

#include "RecDrawer.h"
#include "structs.h"

class Grid;

class Entity
{
public:
	Entity(recData givenRec, vector2D givenPos, vector2DInt givenGridPos);
	virtual ~Entity() {};
	vector2DInt getGridPos() const { return gridPos; };
	void setGridPos(vector2DInt pos);
	virtual void draw() const { rectDrawer.draw(); };
	virtual void tick(float deltaTime) {};
protected:
	vector2DInt gridPos;
	RecDrawer rectDrawer;
};

#endif // !ENTITY_H_DEFINED