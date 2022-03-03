#pragma once

class StateMachine;
class Map;

using namespace std;
class State
{
public:
	State(StateMachine* sM, Map* m);
	State();
	~State();
	StateMachine* stateM;
	Map* map;

	virtual void EnterState() = 0;
	virtual void HandleInput() = 0;
	virtual void Update() = 0;
	virtual void ExitState() = 0;
};

