#pragma once
#include "State.h"
#include "Player.h"

class DoctorState : public State
{
private:
	Player* p_Player;
	void PrintHelp();
public:
	DoctorState();
	DoctorState(StateMachine* sM, Map* m, Player* p);
	~DoctorState();

	void EnterState();

	void HandleInput();

	void Update();

	void ExitState();


	int healCost;
private:

};