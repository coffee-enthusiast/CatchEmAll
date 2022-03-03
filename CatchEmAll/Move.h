#pragma once
#include <string>
#include <iostream>
#include <list>
using namespace std;

enum EntityType;

class Move
{
public:
	string name;
	EntityType type;
	string category;
	int power;
	int accuracy;
	int powerPoints;

public:
	Move();
	Move(string n, EntityType t, string c, int p, int a, int pp);
	string ToString();
};

