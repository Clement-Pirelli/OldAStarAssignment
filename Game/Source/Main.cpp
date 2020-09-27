//
// Code base from: https://www.wikihow.com/Make-a-Cube-in-OpenGL

#define GL_GLEXT_PROTOTYPES

#include "Game.h"
#include "structs.h"
#include <stdlib.h>
#include "glut.h"

#include <random>
#include <ctime>

void display();

const int WINDOW_SIZE_X = 800;
const int WINDOW_SIZE_Y = 800;
const char* WINDOW_NAME = "Pathfinding! yay!!!";


//deltatime stuff
float accumulatedTime = 0.0f;
float lastAccumulatedTime = 0.0f;

Game game;

void keyboard(unsigned char key, int x, int y)
{
	game.keyboard(key, x, y);
}

void display()
{
	accumulatedTime = glutGet(GLUT_ELAPSED_TIME);
	float deltatime = accumulatedTime - lastAccumulatedTime;


	//Clear screen and Z-buffer
	glClearColor(.0f, .0f, .0f, 1.0f); //brown
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	game.tick(deltatime);

	glFlush();
	glutSwapBuffers();

	//ask for new use of display(); 
	glutPostRedisplay();

	lastAccumulatedTime = accumulatedTime;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

    //  Initialize GLUT and process user parameters
    glutInit(&argc,argv);
    
    //  Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Create window
	glutInitWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
    glutCreateWindow(WINDOW_NAME);
    
    //  Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    // Callback functions
    glutDisplayFunc(display);
	glutKeyboardUpFunc(keyboard);

    //  Pass control to GLUT for events
    glutMainLoop();
	
    //  Return to OS
    return 0;
}

