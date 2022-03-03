#pragma once

#include "State.h"
#include "Player.h"
class HomeState : public State
{
private:

	Player* p_Player;
public:
	HomeState(StateMachine* sM, Map* m, Player* p);
	HomeState();
	~HomeState();

	void EnterState();
	void HandleInput();
	void Update();
	void ExitState();

	bool gameEnds;
	void PrintHelp();
private:

};
