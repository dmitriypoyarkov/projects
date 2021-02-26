#pragma once
#include "Scene.h"

class SceneConstructor
{
public:
	static Scene *constructStage(int seed);
	static Scene *constructStarSystem(int seed);
private:
	static void spawnEnemies(int seed, StagePlanet *planet);
	
	static const int MIN_ENEMIES;
	static const int MAX_ENEMIES;
	static const int MIN_ORBIT;
	static const int MAX_ORBIT;
};

