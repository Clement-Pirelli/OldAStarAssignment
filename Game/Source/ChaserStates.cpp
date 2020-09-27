#include "ChaserStates.h"
#include "Starchaser.h"


//COLLECTING
ChaserState_Collecting::ChaserState_Collecting(Starchaser * givenChaser, StateMachine *givenStateMachine) : ChaserState(givenChaser, givenStateMachine)
{
}

ChaserState_Collecting::~ChaserState_Collecting()
{
}

void ChaserState_Collecting::onEnter()
{
	//if the chaser already has a star, it'll go trade it
	if(chaser->getHasStar())
	{
		stateMachine->nextState(new ChaserState_Trading(chaser, stateMachine));
	} else 
	{
		findStar();
	}
}

void ChaserState_Collecting::onExit()
{
}

void ChaserState_Collecting::tick(float deltaTime)
{
	accTime += deltaTime;
	if(accTime>=chaser->actTimer)
	{

		if(!(starPos == chaser->findStar()))
		{
			findStar();
		}

		if (chaser->getGridPos() == starPos && chaser->pickupStar())
		{
			chaser->setHasStar(true);
			if (chaser->getFatigue() >= 100.0f)
			{
				stateMachine->nextState(new ChaserState_Resting(chaser, stateMachine));
				return;
			}
			stateMachine->nextState(new ChaserState_Trading(chaser, stateMachine));
			return;
		}

		//if the starchaser can't move through the path anymore, we try finding the path again
		if(!chaser->moveThroughPath())
		{
			//if the chaser has tried ten times, it'll go rest
			static int tryCount = 0;
			chaser->getPathTo(starPos);
			tryCount++;
			if (tryCount > 10)
			{
				stateMachine->nextState(new ChaserState_Resting(chaser, stateMachine));
				tryCount = 0;
			}
		}

		accTime = 0.0f;
	}
}

void ChaserState_Collecting::findStar()
{
	starPos = chaser->findStar();

	//the starchaser will rest if it cant find a star
	if (starPos.x == -1) stateMachine->nextState(new ChaserState_Resting(chaser, stateMachine));
	//the starchaser will rest if it can't find the path to the star
	if (!chaser->getPathTo(starPos)) stateMachine->nextState(new ChaserState_Resting(chaser, stateMachine));
}

//RESTING
ChaserState_Resting::ChaserState_Resting(Starchaser * givenChaser, StateMachine *givenStateMachine) : ChaserState(givenChaser, givenStateMachine)
{
}

ChaserState_Resting::~ChaserState_Resting()
{
}

void ChaserState_Resting::onEnter()
{
	shipPos = chaser->findShip();
	chaser->getPathTo(shipPos);
}

void ChaserState_Resting::onExit()
{
}

void ChaserState_Resting::tick(float deltaTime)
{
	accTime += deltaTime;
	if (accTime >= chaser->actTimer)
	{
		accTime = 0.0f;
		if (!(shipPos == chaser->findShip()))
		{
			shipPos = chaser->findShip();
			chaser->getPathTo(shipPos);
		}

		if (chaser->getGridPos() == shipPos)
		{
			chaser->restTick();
			if (chaser->getFatigue() <= 0.1f) stateMachine->nextState(new ChaserState_Collecting(chaser, stateMachine));
			return;
		}

		//if the starchaser can't move through the path anymore, we try finding the path again
		if (!chaser->moveThroughPath())
		{
			chaser->getPathTo(shipPos);
		}

		
	}
}

//TRADING
ChaserState_Trading::ChaserState_Trading(Starchaser * givenChaser, StateMachine *givenStateMachine) : ChaserState(givenChaser, givenStateMachine)
{
}

ChaserState_Trading::~ChaserState_Trading()
{
}

void ChaserState_Trading::onEnter()
{
	traderPos = chaser->findTrader();
	chaser->getPathTo(traderPos);

	if (!chaser->getHasStar())
		stateMachine->nextState(new ChaserState_Collecting(chaser, stateMachine));
}

void ChaserState_Trading::onExit()
{
}

void ChaserState_Trading::tick(float deltaTime)
{
	accTime += deltaTime;
	if (accTime >= chaser->actTimer)
	{

		if(!(traderPos == chaser->findTrader()))
		{
			traderPos = chaser->findTrader();
			chaser->getPathTo(traderPos);
		}


		if (chaser->getGridPos() == traderPos)
		{
			//the chaser has traded its star
			chaser->setHasStar(false);
			if(chaser->getFatigue() >= 100.0f)
			{
				stateMachine->nextState(new ChaserState_Resting(chaser, stateMachine));
				return;
			}
			stateMachine->nextState(new ChaserState_Collecting(chaser, stateMachine));
			return;
		}

		//if the starchaser can't move through the path anymore, we try finding the path again
		if (!chaser->moveThroughPath())
		{
			//if the chaser has tried ten times, it'll go rest
			static int tryCount = 0;
			chaser->getPathTo(traderPos);
			tryCount++;
			if(tryCount > 10)
			{
				stateMachine->nextState(new ChaserState_Resting(chaser, stateMachine));
				tryCount = 0;
			}
		}

		accTime = 0.0f;
	}
}
