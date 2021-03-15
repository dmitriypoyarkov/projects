#include "Statistics.h"

bool Statistics::cheatUsingState = false;

int Statistics::clearedStages = 0;
int Statistics::clearedStarSystems = 0;
int Statistics::destroyedEnemies = 0;

void Statistics::reset()
{
	cheatUsingState = false;
	clearedStages = 0;
	clearedStarSystems = 0;
	destroyedEnemies = 0;
}

void Statistics::addClearedStage()
{
	if (cheatUsingState) return;
	clearedStages++;
}

void Statistics::addClearedStarSystem()
{
	if (cheatUsingState) return;
	clearedStarSystems++;
}

void Statistics::addDestroyedEnemy()
{
	if (cheatUsingState) return;
	destroyedEnemies++;
}

void Statistics::setCheatUsingState(bool newState)
{
	reset();
	cheatUsingState = newState;
}

void Statistics::show()
{
	std::cout << "\tStatistics:" << std::endl;
	if (cheatUsingState)
	{
		std::cout << "Cheats detected; statistics not available.: " + std::to_string(clearedStages) << std::endl;
	}
	else
	{
		std::cout << "Cleared stages: " + std::to_string(clearedStages) << std::endl;
		std::cout << "Cleared star systems: " + std::to_string(clearedStarSystems) << std::endl;
		std::cout << "Destroyed enemies: " + std::to_string(destroyedEnemies) << std::endl;
	}
}
