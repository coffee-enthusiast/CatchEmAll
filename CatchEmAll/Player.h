#pragma once

#include <iostream>
#include <list>
using namespace std;

class Entity;

class Player
{
private:
	list<Entity*> myCreatures;
	string s_Name;
	int m_Tokens;
public:
	Player();
	Player(string name);
	~Player();
	string getName();
	int getTokens();
	void changeTokens(int value);
	void AddCreature(Entity* creature);
	void AddCreature(Entity* creature, int index);
	Entity* GetCreature(int index);
	int GetCreaturesNumber();
	void PrintMyCreatures();
};

