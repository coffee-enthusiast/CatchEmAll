#include "Entity.h"

#include "Player.h"


string Entity::TypeToString()
{
	switch (m_Type)
	{
	case NORMAL:
		return "NORMAL";
	case FIRE:
		return "FIRE";
	case WATER:
		return "WATER";
	case ICE:
		return "ICE";
	case ELECTRIC:
		return "ELECTRIC";
	case GRASS:
		return "GRASS";
	default:
		return "-";
	}
}

Entity::Entity()
{
}

Entity::Entity(string name, EntityType type, int maxHp, int attack, int defence, int spAt, int spDef, int speed, int evolLevel, int nextEvolLevel)
{
	m_Name = name;
	m_Type = type;
	m_MaxHealth = maxHp;
	m_Health = maxHp;
	attackPoints = attack;
	defendPoints = defence;
	specialAttackPoints = spAt;
	specialDefencePoints = spDef;
	speedPoints = speed;
	evolutionLevel = evolLevel;
	levelToEvolve = nextEvolLevel;

	m_Level = 0;
}

Entity::~Entity()
{
}

string Entity::getName()
{
	return m_Name;
}

EntityType Entity::getType()
{
	return m_Type;
}

int Entity::getLevel()
{
	return m_Level;
}

void Entity::setLevel(int prevLevel, int nextLevel)
{

	if (prevLevel == 0)
	{
		m_Level = rand() % levelToEvolve;
		if (m_Level == 0)
			m_Level = 1;
	}
	else
	{

		if (nextLevel == 0)
			m_Level = prevLevel + 1;
		else
			m_Level = prevLevel + rand() % (nextLevel - prevLevel);
	}
}

void Entity::addExpPoints(int value)
{
	cout << m_Name << " just got " << to_string(value) << " xp!" << endl;
	m_expPoints += value;
	while (m_expPoints >= 10)
	{
		growUp();
		m_expPoints -= 10;
	}
}

int Entity::getExpPoints()
{
	return m_expPoints;
}

void Entity::TakeDamage(int value)
{
	m_Health -= value;
	if (m_Health < 0)
		m_Health = 0;
}

void Entity::Heal(int value)
{
	m_Health += value;
	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;
}

void Entity::FullHeal()
{
	m_Health = m_MaxHealth;
}

int Entity::getHealth()
{
	return m_Health;
}

int Entity::getAttack()
{
	return attackPoints;
}

int Entity::getDefence()
{
	return defendPoints;
}

int Entity::getPowerPoints()
{
	return powerPoints;
}

void Entity::changePowerPoints(int value)
{
	powerPoints -= value;
	if (powerPoints < 0)
		powerPoints = 0;
}

void Entity::setNextLevel(Entity* nextEntity)
{
	p_nextEvolutionEntity = nextEntity;
}

int Entity::getCurrEvolutLevel()
{
	return evolutionLevel;
}

int Entity::getNextEvolutLevel()
{
	return levelToEvolve;
}


void Entity::growUp()
{
	m_Level++;
	cout << m_Name << " just leveled up! Lvl: " << to_string(m_Level) << endl;
	if (m_Level == levelToEvolve)
	{
		cout << m_Name << " just evolved to a ";
		m_Name = p_nextEvolutionEntity->getName();
		cout << m_Name << " !!!" << endl;

		m_MaxHealth = p_nextEvolutionEntity->getHealth();
		m_Health = m_MaxHealth;
		attackPoints = p_nextEvolutionEntity->getAttack();
		defendPoints = p_nextEvolutionEntity->getDefence();
		powerPoints = p_nextEvolutionEntity->getPowerPoints();

		evolutionLevel = p_nextEvolutionEntity->getCurrEvolutLevel();
		levelToEvolve = p_nextEvolutionEntity->getNextEvolutLevel();
	}
}

string Entity::ToString()
{
	return m_Name + " " + TypeToString() + " Evolution Lvl: "+ to_string(evolutionLevel) + " Lvl: " + to_string(m_Level) + " HP " + to_string(m_Health) + "/" + to_string(m_MaxHealth) + " Att:" + to_string(attackPoints) + " Def:" + to_string(defendPoints);
}

string MovesQuad::TypeToString(EntityType t)
{
	switch (t)
	{
	case NORMAL:
		return "NORMAL";
	case FIRE:
		return "FIRE";
	case WATER:
		return "WATER";
	case ICE:
		return "ICE";
	case ELECTRIC:
		return "ELECTRIC";
	case GRASS:
		return "GRASS";
	default:
		return "-";
	}
}

MovesQuad::MovesQuad()
{
	size = 0;
}

MovesQuad::~MovesQuad()
{
}

void MovesQuad::AddNewMove(Move* newMove)
{
	myMoves[size] = *newMove;
	myMovesExp[size] = 0;
	myMovesLevel[size] = 0;
	size++;
}

void MovesQuad::AddNewMove(Move* newMove, int index)
{
	if (index >= 0 && index < 4)
	{
		myMoves[index] = *newMove;
		myMovesExp[index] = 0;
		myMovesLevel[index] = 0;
		size++;
	}
}

Move MovesQuad::GetMove(int index)
{
	if (index >= 0 && index < 4)
		return myMoves[index];
}

void MovesQuad::UpdateMove(int index, int amount)
{
	if (index >= 0 && index < 4)
	{
		myMovesExp[index] += amount;
		if (myMovesExp[index] >= 10)
		{
			myMovesLevel[index]++;
			myMovesExp[index] -= 10;
		}
	}
}

int MovesQuad::GetMovesNumber()
{
	return size;
}

void MovesQuad::PrintMoves()
{
	for (int i = 0; i < size; i++)
		cout << "\t" <<  to_string(i) << ")" << myMoves[i].name << " " << TypeToString(myMoves[i].type) << " (Power): "
		<< to_string(myMoves[i].power) << " (Acc.): " << to_string(myMoves[i].accuracy) << " (PP): " << to_string(myMoves[i].powerPoints) << endl;
}
