#pragma once
#include "ArenaState.h"
#include "DoctorState.h"
#include "HomeState.h"
#include "WalkState.h"

class Map
{
public:
	Map();
	~Map();

	void LinkMapLocations(HomeState* home, DoctorState* doctor, WalkState* walk, ArenaState* arena);
	ArenaState* arenaLocation;
	DoctorState* doctorLocation;
	HomeState* homeLocation;
	WalkState* walkLocation;
};

