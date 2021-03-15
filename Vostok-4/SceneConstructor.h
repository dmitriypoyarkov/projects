#pragma once
#include "Scene.h"
#include "MiniPlanet.h"

class SceneConstructor
{
public:
	static void constructStarSystem(int seed);
	static void initiateGameWithStarSystem(int seed);
private:
	static void spawnEnemies(int seed, Planet *planet);
	static Star *createStar(unsigned seed);
	static void createMiniPlanets(int seed, Star *star);
	static void starSystemMessage();

	static Vector2 currentStarPosition;
	static const int FAR_AWAY_DISTANCE_SCALE;
	static const int MIN_ENEMIES;
	static const int MAX_ENEMIES;
	static const int MIN_ORBIT;
	static const int ORBIT_GAP;
	static const int MIN_PLANETS;
	static const int MAX_PLANETS;
	static const int PLANET_SPRITE_SIZE;
	static const int MIN_PLANET_DISTANCE_SCALE;
	static const int MAX_PLANET_DISTANCE_SCALE;
	static const int MIN_PLANET_SPEED;
	static const int MAX_PLANET_SPEED;
	static const int MIN_STAR_SCALE;
	static const int MAX_STAR_SCALE;
	static const int MIN_PLANET_SCALE;
	static const int MAX_PLANET_SCALE;
	static const int PLANET_MASS_UNIT;
};

