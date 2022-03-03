#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::LinkMapLocations(HomeState* home, DoctorState* doctor, WalkState* walk, ArenaState* arena)
{
	arenaLocation = arena;
	doctorLocation = doctor;
	homeLocation = home;
	walkLocation = walk;
}
