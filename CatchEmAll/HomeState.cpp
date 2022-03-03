#include "HomeState.h"
#include <stdio.h>
#include <iostream>

#include "StateMachine.h"
#include "Map.h"
#include "DoctorState.h"

HomeState::HomeState()
{
}

HomeState::HomeState(StateMachine* sM, Map* m, Player* p) : State(sM, m)
{
	p_Player = p;
}


HomeState::~HomeState()
{
}

void HomeState::EnterState()
{
	cout << "Aahh Home Sweet Home!" << endl;
	PrintHelp();
}

void HomeState::HandleInput()
{
	int input = getchar();
	if (input == 'h')
	{
		PrintHelp();
	}
	else if (input == 'a')
	{
		stateM->ChangeState(map->arenaLocation);
	}
	else if (input == 'd')
	{
		stateM->ChangeState(map->doctorLocation);
	}
	else if (input == 'w')
	{
		stateM->ChangeState(map->walkLocation);
	}
	else if (input == 'e')
	{
		gameEnds = true;

	}
	else if (input == 'p')	// Print Creatures command
	{
		p_Player->PrintMyCreatures();
	}
}

void HomeState::Update()
{
}

void HomeState::ExitState()
{
}

void HomeState::PrintHelp()
{
	cout << "/--------------Home Location--------------/" << endl;
	cout << "\t-a\tGo To The Arena!" << endl;
	cout << "\t-d\tGo To Doctor!" << endl;
	cout << "\t-w\tGo Out For A Walk!" << endl;
	cout << "\t-h\tHelp" << endl;
	cout << "\t-e\tExit Game!" << endl;
}
