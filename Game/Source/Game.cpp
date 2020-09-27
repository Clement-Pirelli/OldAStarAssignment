#include "Game.h"
#include "Starchaser.h"
#include "Grid.h"
#include "Entity.h"

Game::Game()
{
	vector2DInt chaserPos = {0,0};
	//set the cell at (0, 0) to be grass
	grid.setCellType(Cell::GRASS, vector2DInt{ 0,0 });
	chaser = new Starchaser(
		recData
		{ 
			vector2D{Grid::CELL_DIMENSIONS.x*.3f, Grid::CELL_DIMENSIONS.y*.3f}, 
			color{1.0f, 0.0f, 0.0f}, 0.0f 
		}, 
		Grid::gridToPixel(chaserPos), 
		chaserPos,
		grid,
		entityManager);
	
	addStar();
}

Game::~Game()
{
	delete chaser;
}

void Game::tick(float deltatime)
{
	//star spawning
	if (entityManager.getStar() == nullptr)
	{
		accTime += deltatime;
		if (accTime >= starSpawnRate)
		{
			addStar();
			accTime = 0.0f;
		}
	}

	//tick functions
	grid.tick(deltatime);
	entityManager.tick(deltatime);
	chaser->tick(deltatime);

	//draw functions
	grid.draw();
	entityManager.draw();
	chaser->draw();
}

void Game::keyboard(unsigned char key, int x, int y)
{
	vector2D relativeCoords = { (float)x / (float)glutGet(GLUT_WINDOW_WIDTH), (float)y / (float)glutGet(GLUT_WINDOW_HEIGHT) };
	relativeCoords -= 0.5f;
	relativeCoords *= 2.0f;
	Cell *selectedCell = grid.getCell(relativeCoords);
	if (selectedCell == nullptr) return;

	switch (key)
	{
	case '1':

		//place grass
		grid.setCellType(Cell::GRASS, selectedCell->gridPos);
		
		break;
	case '2':

		//place mountain
		grid.setCellType(Cell::MOUNTAIN, selectedCell->gridPos);

		break;
	case '3':
		
		//place impassable terrain if the starchaser isn't on the tile or if the trader or spaceship are on the tile
		if (chaser->getGridPos() == selectedCell->gridPos || entityManager.getSpaceshipGridPos() == selectedCell->gridPos || entityManager.getTraderGridPos() == selectedCell->gridPos) return;
		
		//placing impassable terrain under a star means it's impossible to get for the chaser
		if (entityManager.getStar() != nullptr)
		{
			if(!(selectedCell->gridPos == entityManager.getStar()->getGridPos()))
				grid.setCellType(Cell::IMPASSABLE, selectedCell->gridPos);
		} else 
		{
			grid.setCellType(Cell::IMPASSABLE, selectedCell->gridPos);
		}

		break;
	case '4':
		if (selectedCell->type != Cell::IMPASSABLE)
			entityManager.addStar(selectedCell->gridPos);
		break;

	case '5':

		if(selectedCell->type != Cell::IMPASSABLE)
			entityManager.setTraderGridPos(selectedCell->gridPos);
		break;

	case '6':
		if (selectedCell->type != Cell::IMPASSABLE)
			entityManager.setSpaceshipGridPos(selectedCell->gridPos);
		break;
	}	
}

void Game::addStar()
{
	for (int i = 0; i < 10; i++)
	{
		vector2DInt starPos = vector2DInt{ rand() % Grid::GRID_SIZE.x, rand() % Grid::GRID_SIZE.y };
		if (starPos == entityManager.getSpaceshipGridPos() || starPos == entityManager.getTraderGridPos() || grid.getCell(starPos)->type != Cell::IMPASSABLE)
		{
			entityManager.addStar(starPos);
			return;
		}
	}
}
