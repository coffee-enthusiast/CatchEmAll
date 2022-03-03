#include "Battle.h"
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "Move.h"

#include <cwchar>
#include <windows.h>
using namespace std;

Battle::Battle()
{
	srand(time(NULL));
}

Battle::~Battle()
{
}


void Battle::PrintPlayerChosenEntities()
{
	for (int i = 0; i < 5; i++)
	{
		if (playerChosenEntities[i] != nullptr)
		{
			cout << to_string(i) << ") " << playerChosenEntities[i]->ToString() << endl;
		}
	}
}

void Battle::PrintRivalChosenEntities()
{
	for (int i = 0; i < 5; i++)
	{
		if (rivalChosenEntities[i] != nullptr)
		{
			cout << to_string(i) << ") " << rivalChosenEntities[i]->ToString() << endl;
		}
	}
}

void Battle::SwapEntities(Entity* currEntity, Entity* newEntity)
{
	if (currEntity == rivalChosenEntity)
	{
		cout << "Rival swaps " << currEntity->getName() << " with " << newEntity->getName() << endl;
		rivalChosenEntity = newEntity;
		whoIsAttacking = player;
	}
	else if (currEntity == playerChosenEntity)
	{
		cout << "Player swaps " << currEntity->getName() << " with " << newEntity->getName() << endl;
		playerChosenEntity = newEntity;
		whoIsAttacking = rival;
	}
	else
	{
		cout << "Error swaping entities!" << endl;
		return;
	}
	
}

bool Battle::deathCheck()
{

	// Check if any entity has health <= 0
	int errorCheck = 0;
	if (playerChosenEntity->getHealth() <= 0)
	{
		playerAliveLeft--;
		if (playerAliveLeft == 0)
		{
			battleEnded = true;
			errorCheck += 1;
		}
	}
	if (rivalChosenEntity->getHealth() <= 0)
	{
		battleEnded = true;
		errorCheck += 2;
	}
	if (battleEnded)
		return errorCheck;

}

float Battle::effectiveAgainstType(EntityType myType, EntityType againtType)
{
	switch (myType)
	{
	case NORMAL:
		return 1;
		break;
	case FIRE:
		if (againtType == NORMAL || againtType == ELECTRIC)
			return 1;
		else if (againtType == FIRE || againtType == WATER)
			return 0.5;
		else if (againtType == GRASS || againtType == ICE)
			return 2;
		break;
	case WATER:
		if (againtType == NORMAL || againtType == ELECTRIC || againtType == ICE)
			return 1;
		else if (againtType == GRASS || againtType == WATER)
			return 0.5;
		else if (againtType == FIRE)
			return 2;
		break;
	case ELECTRIC:
		if (againtType == NORMAL || againtType == FIRE || againtType == ICE)
			return 1;
		else if (againtType == GRASS || againtType == ELECTRIC)
			return 0.5;
		else if (againtType == WATER)
			return 2;
		break;
	case GRASS:
		if (againtType == NORMAL || againtType == ELECTRIC || againtType == ICE)
			return 1;
		else if (againtType == FIRE || againtType == GRASS)
			return 0.5;
		else if (againtType == WATER)
			return 2;
		break;
	case ICE:
		if (againtType == NORMAL || againtType == ELECTRIC)
			return 1;
		else if (againtType == FIRE ||  againtType == ICE || againtType == WATER)
			return 0.5;
		else if (againtType == GRASS)
			return 2;
		break;
	}

	return 0;
}

int Battle::aiChooseAction()
{
	int currentScore = effectiveAgainstType(rivalChosenEntity->getType(), playerChosenEntity->getType());
	if (currentScore >= 1 && rivalChosenEntity->getHealth() > 0)
		return 0;	// Everything is fine, fight!

	float score;
	int bestIndex = -1;
	float bestScore = 0;
	// If not, check if you have a better entity to fight against the opponent
	for (int index = 0; index < rival->GetCreaturesNumber(); index++)
	{
		if (rivalChosenEntities[index]->getHealth() <= 0)
			continue;

		score = effectiveAgainstType(rivalChosenEntities[index]->getType(), playerChosenEntity->getType());
		if (score > bestScore)
		{
			
			bestScore = score;
			bestIndex = index;
		}
		else if (score == bestScore && score > 0)
		{
			if (rivalChosenEntities[index]->getHealth() > rivalChosenEntities[bestIndex]->getHealth())
			{
				bestIndex = index;
			}
		}
	}

	// If no better entity found you are destined to lose so run away!
	if (bestIndex == -1)
	{

		cout << "Rival ran away from battle! You win!" << endl;
		battleEnded = true;
		whoWon = player;
		return 2;
	}
	// if best score is greater then swap
	// if best score is equal but another entity(let b) is chosen that means that b has better health so swap with b
	else if (bestScore >= currentScore && rivalChosenEntity != rivalChosenEntities[bestIndex])
	{
		SwapEntities(rivalChosenEntity, rivalChosenEntities[bestIndex]);
		return 1;	// Rival's round ended
	}
	else {
		cout << "Rival has no clue what to do next! Nevermind!" << endl;
		return 0;
	}
}

void Battle::rivalAttacks()
{

	// If chosenEntity is effective againt opponent then Use a Move
	if (aiChooseAction() == 0)
	{
		// Choose a random move
		Move myMove;
		do
		{
			myMove = rivalChosenEntity->myMovesQuad.GetMove(rand() % rivalChosenEntity->myMovesQuad.size);
		} while (myMove.name == "");

		if(myMove.category == "Physical")
		{
			// Calculate and Take damage from the rival entity

			cout << rival->getName() << " used " << myMove.name << "!" << endl;
			float damage = rivalChosenEntity->getAttack() + myMove.power - playerChosenEntity->getDefence();
			damage *= (float)myMove.accuracy / (float)100;
			damage *= effectiveAgainstType(rivalChosenEntity->getType(), playerChosenEntity->getType());;
			damage /= (float)5;
			playerChosenEntity->TakeDamage(damage);

			rivalChosenEntity->changePowerPoints(myMove.powerPoints);
			
			cout << playerChosenEntity->getName() << " lost " << to_string(damage) << " HP!" << endl;

			if (playerChosenEntity->getHealth() <= 0)
			{
				cout << playerChosenEntity->getName() << " fainted!" << endl;

				rivalChosenEntity->addExpPoints(8);
				playerAliveLeft--;
				if (playerAliveLeft == 0)
				{
					battleEnded = true;
					whoWon = rival;
				}
			}
		}
	}
	

}

void Battle::playerAttacks()
{

	cout << "My entities: " << endl;
	PrintPlayerChosenEntities();
	cout << "Rival's chosen entity: " << rivalChosenEntity->ToString() << endl;

	cout << "Choose your next action: ('m' to choose a move, 's' to swap with another entity, 'e' to exit battle" << endl;
	while (playerChosenEntity->getHealth() <= 0)
	{
		cout << "Choose next entity to fight: ( Health <= 0 )";
		int index;
		cin >> index;
		playerChosenEntity = playerChosenEntities[index];
	}

	char action;
	cin >> action;
	if(action == 'm')	// Use Move
	{
		cout << "Choose index of move:" << endl;
		playerChosenEntity->myMovesQuad.PrintMoves();

		int index;
		cin >> index;
		Move myMove = playerChosenEntity->myMovesQuad.GetMove(index);
		cout << player->getName() << " used " << myMove.name << "!" <<endl;

		if (myMove.category == "Physical")
		{
			// Calculate and Take damage from the rival entity
			float damage = playerChosenEntity->getAttack() + myMove.power - rivalChosenEntity->getDefence();
			damage *= (float)myMove.accuracy / (float)100;
			damage *= effectiveAgainstType(playerChosenEntity->getType(), rivalChosenEntity->getType());
			damage /= (float)5;
			rivalChosenEntity->TakeDamage(damage);

			playerChosenEntity->changePowerPoints(myMove.powerPoints);

			cout << rivalChosenEntity->getName() << " lost " << to_string(damage) << " HP!" << endl;

			if (rivalChosenEntity->getHealth() <= 0)
			{
				cout << rivalChosenEntity->getName() << " fainted!" << endl;
				playerChosenEntity->addExpPoints(8);
				rivalAliveLeft--;
				if (rivalAliveLeft == 0)
				{
					battleEnded = true;
					whoWon = player;
				}
				else
				{
					// Choose next to fight for the rival
					if(aiChooseAction() <= 1)
						playerAttacks();
				}
			}
		}
	}
	else if (action == 's')	// Swap
	{
		do {
			cout << "Choose index of next entity:" << endl;
			int index;
			cin >> index;

			SwapEntities(playerChosenEntity, playerChosenEntities[index]);
		} while (playerChosenEntity->getHealth() <= 0);
	}
	else if (action == 'e')
	{
		cout << "You ran away from battle! You Lose!" << endl;
		battleEnded = true;
		whoWon = rival;
	}
}

int Battle::setNewMatch(Player* p, Player* r)
{
	player = p;
	rival = r;
	playerAliveLeft = player->GetCreaturesNumber();
	if (!playerAliveLeft)
		return 1;
	rivalAliveLeft = rival->GetCreaturesNumber();
	if (!rivalAliveLeft)
		return 2;

	// Max Index will be 5 if rival has more than 5 entities
	// else will be the number of their entities
	int maxIndex = rival->GetCreaturesNumber();
	if (maxIndex > 5)
		maxIndex = 5;

	// Choose maxIndex entities for the rival for this battle
	if (maxIndex < 5)
	{
		for (int index = 0; index < maxIndex; index++)
			rivalChosenEntities[index] = rival->GetCreature(index);
	}
	else // maxIndex == 5
	{
		// Iterate through each rival's entity and choose randomly if it will be chosen
		// but if you are at the last leftToChoose entities then choose them!
		int leftToChoose = 5;
		int i = 0;
		for (int index = 0; index < rival->GetCreaturesNumber(); index++, i++)
		{
			if (leftToChoose == 0)
				break;
			else if (leftToChoose == rival->GetCreaturesNumber() - index)
			{
				rivalChosenEntities[index] = rival->GetCreature(i);
				leftToChoose--;
			}
			else
			{
				bool choice = rand() % 2;
				if (choice == true)
				{
					rivalChosenEntities[index] = rival->GetCreature(i);
					leftToChoose--;
				}
			}
		}
	}
		
	

	rivalIndexChoice = 0;
	rivalChosenEntity = rivalChosenEntities[rivalIndexChoice];

	cout << "Rival has chosen these " << to_string(maxIndex) << " entities to fight:" << endl;
	PrintRivalChosenEntities();

	// Ask from player to give their maxIndex entities
	maxIndex = player->GetCreaturesNumber();
	if (maxIndex > 5)
		maxIndex = 5;

	cout << "Give the indexes of your " << to_string(maxIndex) << " entities that will fight!" << endl;
	player->PrintMyCreatures();
	for (int i = 0; i < maxIndex; i++)
	{
		int givenIndex;
		cin >> givenIndex;
		if (player->GetCreature(givenIndex) != nullptr)
			playerChosenEntities[i] = player->GetCreature(givenIndex);
	}
	cout << "You have chosen:" << endl;
	PrintPlayerChosenEntities();

	whoIsAttacking = player;
	battleRound = 0;
	battleEnded = false;

}

void Battle::StartBattle(Player* p, Player* r)
{
	FlushData();

	int matchErrors = setNewMatch(p, r);
	switch (matchErrors)
	{
	case 0:
		break;
	case 1:
		cout << "Battle can't start due to:" << endl;
		cout << "\tFirst player hasn't any creatures left to fight!( Health <= 0)" << endl;
		return;
	case 2:
		cout << "Battle can't start due to:" << endl;
		cout << "\tSecond player hasn't any creatures left to fight!( Health <= 0)" << endl;
		return;
	}

	cout << battleInfo() << endl;
	cout << "Rival has chosen " << rivalChosenEntity->ToString() << " to start the fight!" << endl;
	// Choose starting entity for player
	int index;
	do
	{
		cout << "Choose entity to fight first:" << endl;
		cin >> index;
		playerChosenEntity = playerChosenEntities[index];
	} while (playerChosenEntity == nullptr);

	whoIsAttacking = player;

	while (!battleEnded)
	{
		cout << roundInfo() << endl;

		whoIsAttacking = player;
		playerAttacks();

		whoIsAttacking = rival;
		rivalAttacks();
		
		battleRound++;
	}

	cout << battleResult() << endl;
}

void Battle::FlushData()
{
	player = nullptr;
	rival = nullptr;
	battleEnded = false;
	
	for (int i = 0; i < 5; i++)
	{
		playerChosenEntities[i] = nullptr;
		rivalChosenEntities[i] = nullptr;
	}
}

string Battle::battleInfo()
{
	return player->getName() + " will fight with " + rival->getName();
}

string Battle::roundInfo()
{
	return "Round " + to_string(battleRound) + "\n" + whoIsAttacking->getName() + " attacks!\n";
}

string Battle::battleResult()
{
	return "Battle ends! Winner is ...\n\t" + whoWon->getName();
}
