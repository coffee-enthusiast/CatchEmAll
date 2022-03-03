#include "Player.h"

#include "Entity.h"
#include <iterator>
using namespace std;

Player::Player()
{
}

Player::Player(string name)
{
	s_Name = name;
	m_Tokens = 100;
}

Player::~Player()
{
}

string Player::getName()
{
	return s_Name;
}

int Player::getTokens()
{
	return m_Tokens;
}

void Player::changeTokens(int value)
{
	m_Tokens += value;
}

void Player::AddCreature(Entity* creature)
{
	myCreatures.push_back(creature);
}

void Player::AddCreature(Entity* creature, int index)
{
	myCreatures.insert(myCreatures.begin(),index, creature);
}

Entity* Player::GetCreature(int index)
{
	if (index < myCreatures.size())
	{
		auto it = myCreatures.begin();
		for (int i = 0; i < index; i++)
			it++;

		return *it;
	}
	return nullptr;
}

int Player::GetCreaturesNumber()
{
	return myCreatures.size();
}

void Player::PrintMyCreatures()
{
	for (auto it = myCreatures.begin(); it != myCreatures.end(); ++it)
	{
		cout << (*it)->ToString() << endl;
		(*it)->myMovesQuad.PrintMoves();
	}
}
