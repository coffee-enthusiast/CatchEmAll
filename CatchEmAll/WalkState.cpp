#include "WalkState.h"

#include "StateMachine.h"
#include "Map.h"
#include "Entity.h"
#include <time.h>

WalkState::WalkState()
{
	srand(time(NULL));
}

WalkState::WalkState(StateMachine* sM, Map* m, Player* p, Library* l) : State(sM, m)
{
	p_Player = p;
	p_Library = l;
	srand(time(NULL));
}

WalkState::~WalkState()
{
}

void WalkState::EnterState()
{
	cout << "The sun is shinning and your greatest adventure lies ahead!" << endl;
	cout << "\tPress 'h' for help!" << endl;

}

void WalkState::HandleInput()
{
	cout << "What's next?" << endl;
	char input;
	cin >> input;

	if (input == 'k')
	{
		KeepWalking();
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

void WalkState::Update()
{
}

void WalkState::ExitState()
{
}

void WalkState::PrintHelp()
{
	cout << "/--------------Walking--------------/" << endl;
	cout << "\t-k\tKeep walking" << endl;
	cout << "\t-h\tHelp" << endl;
	cout << "\t-e\tExit Return to Home!" << endl;
}

void WalkState::KeepWalking()
{
	int random = rand() % 10;
	if (random < 5)
	{
		cout << "Still nothing. Only trees and squirrels!" << endl;
	}
	else
	{
		if (random < 8)	// 5..7 A Creature was found
		{

			cout << "What is that?" << endl;
			cout << "Am I seeing right?" << endl;

			// Spawn a random creature
			random = rand() % p_Library->entitiesList.size();
			Entity* randomCreature = &(p_Library->entitiesList[random]);

			randomCreature->myMovesQuad.AddNewMove(&(p_Library->movesList.getRandomMove(randomCreature->getType())));
			randomCreature->myMovesQuad.AddNewMove(&(p_Library->movesList.getRandomMove(randomCreature->getType())));

			cout << "That is surely a" << endl;
			cout << "\t" << randomCreature->ToString() << endl;

			// Ask if player want's it
			cout << "Enter [y] to pick it up or [n]!\n";

			// Check input and proceed
			char choice;
			cin >> choice;
			if (choice == 'y')
			{
				p_Player->AddCreature(randomCreature);
				cout << randomCreature->getName() << " is now a member of your family!" << endl;
			}
			else {
				cout << "Bye little creature!" << endl;
			}
		}
		else	// 8..9 A collectable item was found
		{
			cout << "A collectable was found!" << endl;
			/*
			cout << "Are you going to pick it up? [y/n]" << endl;
			char choice;
			cin >> choice;
			if (choice == 'y')
			{
				cout << "Great!" << endl;
				int index;

				do {
					cout << "Who will be the lucky one ? " << endl;
					cin >> index;
				} while (index < 0 || index >= p_Player->GetCreaturesNumber());

				if (p_Player->GetCreature(index)->myMovesQuad.GetMovesNumber() == 4)
				{
					int index2;
					do {
						cout << "Your moves list is full! Choose which move to swap:" << endl;
						p_Player->GetCreature(index)->myMovesQuad.PrintMoves();
						cin >> index2;
					} while (index2 < 0 || index2 >= p_Player->GetCreaturesNumber());

					p_Player->GetCreature(index)->myMovesQuad.AddNewMove(&randomMove, index2);
				}else
					p_Player->GetCreature(index)->myMovesQuad.AddNewMove(&randomMove);
			}
			*/
		}
	}
}
