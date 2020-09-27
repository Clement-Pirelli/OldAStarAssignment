#pragma once
#include "State.h"
#include "structs.h"

class StateMachine;
class Starchaser;

class ChaserState : public State
{
public:
	ChaserState(Starchaser *givenChaser, StateMachine *givenStateMachine) : State(givenStateMachine) { chaser = givenChaser; }
	virtual ~ChaserState(){};
protected:
	float accTime = 0.0f;
	Starchaser *chaser;
};


class ChaserState_Collecting : public ChaserState
{
public:
	ChaserState_Collecting(Starchaser *givenChaser, StateMachine *givenStateMachine);
	~ChaserState_Collecting();
	void onEnter() override;
	void onExit() override;

	void tick(float deltaTime) override;

private:
	vector2DInt starPos = vector2DInt{0,0};
	void findStar();
};

class ChaserState_Resting : public ChaserState
{
public:
	ChaserState_Resting(Starchaser *givenChaser, StateMachine *givenStateMachine);
	~ChaserState_Resting();
	void onEnter() override;
	void onExit() override;

	void tick(float deltaTime) override;
private:
	vector2DInt shipPos = vector2DInt{0,0};
};

class ChaserState_Trading : public ChaserState
{
public:
	ChaserState_Trading(Starchaser *givenChaser, StateMachine *givenStateMachine);
	~ChaserState_Trading();
	void onEnter() override;
	void onExit() override;

	void tick(float deltaTime) override;
private:
	vector2DInt traderPos = vector2DInt{ 0,0 };
};