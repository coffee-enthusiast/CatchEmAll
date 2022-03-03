
#include <time.h>
#include "Move.h"

#include "Entity.h"
Move::Move()
{
}

Move::Move(string n, EntityType t, string c, int p, int a, int pp)
{
	name = n;
	type = t;
	category = c;
	power = p;
	accuracy = a;
	powerPoints = pp;
}

string Move::ToString()
{
	return name + " " + to_string(type) + " (Power): " + to_string(power) + 
		" (Acc.): " + to_string(accuracy) + " (PP): " + to_string(powerPoints);
}
