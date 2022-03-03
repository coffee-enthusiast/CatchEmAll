#pragma once
#include "State.h"
#include "Battle.h"
#include "Player.h"
#include "Library.h"

class ArenaState : public State
{
private:
	Library* p_Library;
	Battle battle;
	Player* p_Player;
	int participationCost;
public:
	ArenaState();
	ArenaState(StateMachine* sM, Map* m, Player* p, Library* l);
	~ArenaState();

	void EnterState();
	void HandleInput();
	void Update();
	void ExitState();

private:

	void PrintHelp();
	void StartDuel();
	void StartTournament();
};

