#pragma once
#include "Entity.h"
#include "Move.h"
#include <unordered_map>
#include <vector>


class HashMapTable
{
	// table size is equal to the number of move types("Normal", "Fire", etc.)
	// this game version has 6 types
	int table_size;
	vector<Move>* movesTable;
public:
	HashMapTable();
	HashMapTable(int key);
	// hash function to compute the index using table_size and key
	int hashFunction(int key) {
		return (key % table_size);
	}
	void insertElement(Move newMove);
	Move getRandomMove(EntityType type);
	void displayHashTable();
};

class Library {

public:
	Library();
	vector<Entity> entitiesList;
	HashMapTable movesList;
};