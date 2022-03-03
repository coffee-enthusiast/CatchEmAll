#pragma once
#include "Entity.h"
#include "Player.h"

class Battle
{
public:
	Player* player;
	Player* rival;
	Entity* playerChosenEntity;
	Entity* rivalChosenEntity;

private:
	int battleRound;
	bool battleEnded;
	Player* whoIsAttacking;
	Player* whoWon;
	int playerAliveLeft;
	int rivalAliveLeft;
	int rivalIndexChoice;
	Entity* playerChosenEntities[5];
	Entity* rivalChosenEntities[5];

public:
	Battle();
	~Battle();
	void playerAttacks();
	void rivalAttacks();
	void StartBattle(Player* p, Player* r);
	string battleInfo();
	string roundInfo();
	string battleResult();
private:

	void PrintPlayerChosenEntities();
	void PrintRivalChosenEntities();
	void SwapEntities(Entity* currEntity, Entity* newEntity);
	int aiChooseAction();
	int setNewMatch(Player* p, Player* r);
	void FlushData();
	bool deathCheck();
	float effectiveAgainstType(EntityType myType, EntityType againtType);
};

