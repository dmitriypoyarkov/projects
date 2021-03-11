#pragma once
#include "Scene.h"
#include "MiniPlanet.h"

class SceneConstructor
{
public:
	static Scene *constructStage(int seed);
	static Scene *constructStarSystem(int seed);
private:
	static void spawnEnemies(int seed, StagePlanet *planet);
	static MiniPlanet *createStar(unsigned seed);
	static void createMiniPlanets(int seed, MiniPlanet *star);
	static const int MIN_ENEMIES;
	static const int MAX_ENEMIES;
	static const int MIN_ORBIT;
	static const int MAX_ORBIT;
	static const int MIN_PLANETS;
	static const int MAX_PLANETS;
	static const int MIN_PLANET_DISTANCE;
	static const int MAX_PLANET_DISTANCE;
	static const int MIN_PLANET_SPEED;
	static const int MAX_PLANET_SPEED;
};

