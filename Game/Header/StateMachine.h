#pragma once
#include "State.h"

class StateMachine
{
public:
	StateMachine(State *firstState = nullptr){ currentState = firstState; };
	~StateMachine(){};

	void tick(float deltaTime);
	void nextState(State *givenState);
	void setFirstState(State *givenState);

protected :

	State *currentState = nullptr;
	State *lastState = nullptr;
};