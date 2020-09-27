#include "StateMachine.h"

void StateMachine::tick(float deltaTime)
{
	//can't delete the last state right away since that would mean not getting out of the scope where the lastState called its own destruction
	if(lastState != nullptr) 
	{
		delete lastState;
		lastState = nullptr;
	}

	if (currentState != nullptr)
		currentState->tick(deltaTime);
}

void StateMachine::nextState(State *givenState)
{
	if (lastState != nullptr)
		delete lastState;

	currentState->onExit();
	lastState = currentState;
	currentState = givenState;
	currentState->onEnter();
}

void StateMachine::setFirstState(State * givenState)
{
	if (currentState == nullptr)
	{
		currentState = givenState;
		currentState->onEnter();
	} 
}

