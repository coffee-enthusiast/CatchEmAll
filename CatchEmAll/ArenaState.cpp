#include "ArenaState.h"

#include "StateMachine.h"
#include "Map.h"

ArenaState::ArenaState()
{
}

ArenaState::ArenaState(StateMachine* sM, Map* m, Player* p, Library* l) : State(sM, m)
{
	p_Library = l;
	p_Player = p;
	participationCost = 100;
}

ArenaState::~ArenaState()
{
}

void ArenaState::EnterState()
{
	cout << "Welcome " << p_Player->getName() << "," << endl;

}

void ArenaState::HandleInput()
{
	cout << "Which challenge will be the next?" << endl;

	int input = getchar();
	if (input == 'h')
	{
		PrintHelp();
	}
	else if (input == 'd')	// Duel
	{
		StartDuel();
	}
	else if (input == 't')	// Tournament
	{
		StartTournament();
	}
	else if (input == 'e')
	{
		stateM->ChangeState(map->homeLocation);

	}
	else if (input == 'p')	// Print Creatures command
	{
		p_Player->PrintMyCreatures();
	}
}
void ArenaState::Update()
{

}
void ArenaState::ExitState()
{

}

void ArenaState::PrintHelp()
{
	cout << "/--------------Arena Location--------------/" << endl;
	cout << "\t-d\tDuel!" << endl;
	cout << "\t-t\tTournament!" << endl;
	cout << "\t-h\tHelp!" << endl;
	cout << "\t-e\tExit Game!" << endl;
}

void ArenaState::StartDuel()
{
	cout << "You were drawn to a duel with..." << endl;
	Player* randomPlayer = new Player("Random Player");
	cout << " " << randomPlayer->getName() << endl;

	// Set a rival
	Entity randomEntity = p_Library->entitiesList[rand() % p_Library->entitiesList.size()];
	Move randMove = p_Library->movesList.getRandomMove(randomEntity.getType());
	randomEntity.myMovesQuad.AddNewMove(&randMove);

	randomPlayer->AddCreature(&randomEntity);

	Entity randomEntity2 = p_Library->entitiesList[rand() % p_Library->entitiesList.size()];
	Move randMove2 = p_Library->movesList.getRandomMove(randomEntity2.getType());
	randomEntity2.myMovesQuad.AddNewMove(&randMove2);

	randomPlayer->AddCreature(&randomEntity2);

	// Start de matchaa
	battle.StartBattle(p_Player, randomPlayer);
}

void ArenaState::StartTournament()
{
	if (p_Player->getTokens() >= participationCost)
	{
		p_Player->changeTokens(-participationCost);
	}
	else
	{
		cout << "Sorry, you don't have the tokens needed!\nParticipation Cost: " << participationCost << "\nAvailable Tokens: " << to_string(p_Player->getTokens()) << endl;
	}
}
