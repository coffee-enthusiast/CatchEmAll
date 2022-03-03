#pragma once
#include "State.h"
class StateMachine
{


public:
	StateMachine(State* startingState);
	StateMachine();
	~StateMachine();
	State* currentState;
	void ChangeState(State* newState);
};

