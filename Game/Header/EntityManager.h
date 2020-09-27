#pragma once
#include "Entity.h"
#include "structs.h"

#ifndef ENTITYMANAGER_H_DEFINED
#define ENTITYMANAGER_H_DEFINED

class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	
	void tick(float deltatime);
	void draw();

	vector2DInt getSpaceshipGridPos();
	vector2DInt getTraderGridPos();
	
	Entity *getStar();
	void addStar(vector2DInt pos);
	bool removeStar(vector2DInt pos);

	void setSpaceshipGridPos(vector2DInt pos);
	void setTraderGridPos(vector2DInt pos);
	
private:
	recData SPACESHIP_REC;
	recData TRADER_REC;
	recData STAR_REC;

	Entity *spaceship = nullptr;
	Entity *trader = nullptr;
	Entity *star = nullptr;
};

#endif