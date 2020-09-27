#pragma once
#include "Entity.h"
#include "Astarrer.h"
#include "LineRenderer.h"
#include "StateMachine.h"

class Grid;
class EntityManager;

class Starchaser : public Entity, Astarrer
{
public:
	Starchaser(recData givenRec, vector2D givenPos, vector2DInt givenGridPos, const Grid &givenGrid, EntityManager &givenEntityManager);
	~Starchaser();
	void tick(float deltaTime) override;
	bool getPathTo(vector2DInt destination);
	void draw() const override;
	bool moveThroughPath();
	vector2DInt getGridPos(){ return gridPos; };


	void setHasStar(bool givenHasStar){ hasStar = givenHasStar; }
	bool getHasStar(){ return hasStar; }

	float getFatigue(){ return fatigue; }
	void incrementFatigue(float increment){ fatigue += increment; if (fatigue < 0.0f) fatigue = 0.0f; if (fatigue > maxFatigue) fatigue = maxFatigue; }
	void restTick(){ incrementFatigue(-fatigueIncrement); }

	vector2DInt findStar();
	bool pickupStar();

	vector2DInt findTrader();
	vector2DInt findShip();

	const float actTimer = 100.0f;

private:
	LineRenderer lineRenderer = LineRenderer(std::vector<vector2D>(), color{1.0f, 0.0f, 0.0f}, 0.0f);
	StateMachine stateMachine;
	bool hasStar = false;

	const Grid &grid;
	EntityManager &entityManager;

	float fatigue = 0.0f;
	const float fatigueIncrement = 1.0f;
	const float maxFatigue = 120.0f;

	std::vector<vector2DInt> path;
};