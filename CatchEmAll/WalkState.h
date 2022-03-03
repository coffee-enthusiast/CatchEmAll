#pragma once
#include "Library.h"
#include "State.h"
#include "Player.h"
#include "Move.h"

class WalkState : public State
{
private:
	Player* p_Player;
	Library* p_Library;
public:
	WalkState();
	WalkState(StateMachine* sM, Map* m, Player* p, Library* l);
	~WalkState();

	void EnterState();
	void HandleInput();
	void Update();
	void ExitState();

private:

	void PrintHelp();
	void KeepWalking();
};

