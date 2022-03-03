#pragma once

#include <string>
using namespace std;

#include "Move.h"


class MovesQuad
{
	Move myMoves[4];
	int myMovesExp[4];
	int myMovesLevel[4];
private:
	string TypeToString(EntityType t);
public:
	MovesQuad();
	~MovesQuad();

	int size;
	void AddNewMove(Move* newMove);
	void AddNewMove(Move* newMove, int index);
	Move GetMove(int index);
	void UpdateMove(int index, int amount);
	int GetMovesNumber();
	void PrintMoves();
};

enum EntityType
{
	NORMAL,
	FIRE,
	WATER,
	ELECTRIC,
	GRASS,
	ICE
};

class Entity
{
private:
	string m_Name;
	EntityType m_Type;
	int m_Level;
	int m_expPoints;
	int m_Health;
	int m_MaxHealth;
	int attackPoints;
	int defendPoints;
	int specialAttackPoints;
	int specialDefencePoints;
	int speedPoints;
	int powerPoints;

	int evolutionLevel;
	int levelToEvolve;

	Entity* p_nextEvolutionEntity;
private:
	string TypeToString();
public:
	Entity();
	Entity(string name, EntityType type, int maxHp, int attack, int defence, int spAt, int spDef, int speed, int evolLevel, int nextEvolLevel);
	~Entity();

	string getName();
	EntityType getType();
	int getLevel();
	void setLevel(int prevLevel, int nextLevel);
	void addExpPoints(int value);
	int getExpPoints();
	void TakeDamage(int value);
	void Heal(int value);
	void FullHeal();
	int getHealth();
	int getAttack();
	int getDefence();
	int getPowerPoints();
	void changePowerPoints(int value);
	void setNextLevel(Entity* nextEntity);

	int getCurrEvolutLevel();
	int getNextEvolutLevel();
	void growUp();
	string ToString();
public:
	MovesQuad myMovesQuad;
};

