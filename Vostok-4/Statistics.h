#pragma once

class Statistics
{
private:
	Statistics();
	static bool cheatUsingState;

	static int clearedStages;
	static int clearedStarSystems;
	static int destroyedEnemies;
public:
	static void reset();
	static void addClearedStage();
	static void addClearedStarSystem();
	static void addDestroyedEnemy();

	static void setCheatUsingState(bool newState);
	static void show();
};