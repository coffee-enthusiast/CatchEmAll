#include "Library.h"
#include <time.h>

HashMapTable::HashMapTable()
{
	this->table_size = 6;
	srand(time(NULL));
}

HashMapTable::HashMapTable(int ts)
{
	this->table_size = ts;
	movesTable = new vector<Move>[table_size];
	srand(time(NULL));
}

void HashMapTable::insertElement(Move newMove)
{
	int index = hashFunction(newMove.type);
	movesTable[index].push_back(newMove);
}

Move HashMapTable::getRandomMove(EntityType type)
{
	return movesTable[type][rand() % movesTable[type].size()];
}

void HashMapTable::displayHashTable() {
	for (int i = 0; i < table_size; i++) {
		cout << i;
		// traversing at the recent/ current index
		for (auto j : movesTable[i])
			cout << " ==> " << j.ToString();
		cout << endl;
	}
}

Library::Library()
{
	movesList = HashMapTable(6);
}
