#include "DoctorState.h"
#include "Entity.h"
#include "StateMachine.h"
#include "Map.h"
#include <iostream>

void DoctorState::PrintHelp()
{
	cout << "/--------------Doctor State--------------/" << endl;
	cout << "\t-t[index]\tTreat your animal with the same index as shown in your creatures list! Cost:" 
		<< to_string(healCost) << " Tokens for each injured animal!" << endl;
	cout << "\t-h\tHelp" << endl;
	cout << "\t-e\tExit Return to Home!" << endl;
}

DoctorState::DoctorState()
{
	healCost = 30;
}

DoctorState::DoctorState(StateMachine* sM, Map* m, Player* p) : State(sM, m)
{
	p_Player = p;
	healCost = 30;
}

DoctorState::~DoctorState()
{
}

void DoctorState::EnterState()
{
	cout << "Welcome " << p_Player->getName() << ",\n";
	cout << "How can I help you?\n";
	cout << "\tPress 'h' for help!" << endl;
}

void DoctorState::HandleInput()
{
	int input = getchar();

	if (input == 't')
	{
		int index;
		cin >> index;
		if (index >= 0)
		{
			if (p_Player->GetCreature(index) != nullptr && p_Player->getTokens() >= healCost)
			{
				p_Player->GetCreature(index)->FullHeal();
				p_Player->changeTokens(-healCost);
				cout << p_Player->GetCreature(index)->getName() << " already feels better!" << endl;

			}
			else
			{
				cout << "Sorry invalid index given or not enough tokens!\nIndex goven: " + to_string(index) + "\nPlayer Tokens: " + to_string(p_Player->getTokens()) << endl;
			}
		}
		else
		{
			cout << "Sorry invalid index given!" << endl;
		}
	}
	else if (input == 'e')	// Exit command
	{
		stateM->ChangeState(map->homeLocation);
	}
	else if (input == 'h')	// Help command
	{
		PrintHelp();
	}
	else if (input == 'p')	// Print Creatures command
	{
		p_Player->PrintMyCreatures();
	}
}

void DoctorState::Update()
{
}

void DoctorState::ExitState()
{
}
