#include "StateMachine.h"

StateMachine::StateMachine(State* startingState)
{
	currentState = startingState;
}

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::ChangeState(State* newState)
{

	if(currentState != nullptr)
		currentState->ExitState();

	currentState = newState;

	currentState->EnterState();
}
