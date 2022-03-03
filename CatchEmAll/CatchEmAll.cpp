// CatchEmAll.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Library.h"
#include "Entity.h"
#include "Player.h"
#include "Battle.h"
#include "StateMachine.h"
#include "Map.h"
#include "HomeState.h"
#include "WalkState.h"
#include "Move.h"

#include <fstream>
#include <vector>


void InitEntities(vector<Entity>* list)
{

	ifstream myFile;
	myFile.open("./DataFiles/Entities.txt", ios::in);
	string  name, type;
	int hp, att, def, spAtt, spDef, speed, currLevel, nextLevel;
	int index = 0;
	Entity* prevEntity = new Entity();
	while (myFile >> name)
	{
		myFile >> type >> hp >> att >> def >> spAtt >> spDef >> speed >> currLevel >> nextLevel;

		EntityType enType = (EntityType)NORMAL;
		if(type == "FIRE")
			enType = (EntityType)FIRE;
		else if (type == "WATER")
			enType = (EntityType)WATER;
		else if (type == "ELECTRIC")
			enType = (EntityType)ELECTRIC;
		else if (type == "GRASS")
			enType = (EntityType)GRASS;
		else if (type == "ICE")
			enType = (EntityType)ICE;
		else if (type == "NORMAL")
			enType = (EntityType)NORMAL;

		Entity newEntity = Entity(name, enType, hp, att, def, spAtt, spDef, speed, currLevel, nextLevel);
		if (currLevel > 1)
			prevEntity->setNextLevel(&newEntity);

		prevEntity = &newEntity;
		if(newEntity.getCurrEvolutLevel() == 1)
			newEntity.setLevel(0, nextLevel);
		else
			newEntity.setLevel(list->at(index - 1).getNextEvolutLevel(), nextLevel);

		list->push_back(newEntity);
		index++;
	}

	myFile.close();
}

void InitMoves(Library* l)
{

	ifstream myFile;
	myFile.open("./DataFiles/Moves.txt", ios::in);
	string  name, type, category;
	int power, acc, pp;

	while (myFile >> name)
	{
		myFile >> type >> category >> power >> acc >> pp;

		EntityType enType;
		if (type == "FIRE")
			enType = (EntityType)FIRE;
		else if (type == "WATER")
			enType = (EntityType)WATER;
		else if (type == "ELECTRIC")
			enType = (EntityType)ELECTRIC;
		else if (type == "GRASS")
			enType = (EntityType)GRASS;
		else if (type == "ICE")
			enType = (EntityType)ICE;
		else
			enType = (EntityType)NORMAL;

		Move newMove = Move(name, enType, category, power, acc, pp);
		l->movesList.insertElement(newMove);
	}

	myFile.close();
}

bool FileExists(string filename)
{
	ifstream file(filename);
	if (file.is_open())
	{
		return 1;
		file.close();
	}
	else
	{
		return 0;
	}
}
int main()
{
	Library myLibrary = Library();
	// Initialize pokemons List
	InitEntities(&myLibrary.entitiesList);
	// Initialize moves List
	InitMoves(&myLibrary);
	//myLibrary.movesList.displayHashTable();

	Player* marios = new Player("Marios");

	StateMachine* stateMachine = new StateMachine();

	Map globalMap = Map();
	HomeState myHome = HomeState(stateMachine, &globalMap, marios);
	DoctorState myDoctor = DoctorState(stateMachine, &globalMap, marios);
	WalkState myWalk = WalkState(stateMachine, &globalMap, marios, &myLibrary);
	ArenaState myArena = ArenaState(stateMachine, &globalMap, marios, &myLibrary);

	globalMap.LinkMapLocations(&myHome, &myDoctor, &myWalk, &myArena);

	stateMachine->ChangeState(&myHome);

	bool endGame = false;

	while (!myHome.gameEnds)
	{
		stateMachine->currentState->HandleInput();

		stateMachine->currentState->Update();

		endGame = true;
	}

	/*
	Battle stadium = Battle();

	stadium.StartBattle(&flowerBeast, &beeExorcist);
	cout << beeExorcist.ToString() << endl;
	stadium.StartBattle(marios->GetCreature(0), &beeExorcist);
	cout << beeExorcist.ToString() << endl;
	*/
	return 0;
}
