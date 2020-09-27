#pragma once
#include "Grid.h"
#include "EntityManager.h"


class Starchaser;

class Game
{
public:
	Game();
	~Game();
	void tick(float deltatime);
	void keyboard(unsigned char key, int x, int y);
private:

	Grid grid;
	EntityManager entityManager;

	Starchaser *chaser;
	
	

	float starSpawnRate = 400.0f;
	float accTime = 0.0f;
	void addStar();
};