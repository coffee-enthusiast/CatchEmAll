#include "State.h"
#include "StateMachine.h"
#include "Map.h"
State::State(StateMachine* sM, Map* m)
{
	stateM = sM;
	map = m;
}

State::State()
{
}

State::~State()
{
}

