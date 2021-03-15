#include "SceneConstructor.h"
#include <iostream>
#include "EnemyShip.h"

void SceneConstructor::initiateGameWithStarSystem(int seed)
{
	new Camera();
	Star *star = createStar(seed);
	Scene::setActiveStar(star);
	createMiniPlanets(seed, star);
	new PlayerShip(star, star->getSurfaceRadius() + 800);
	starSystemMessage();
}

void SceneConstructor::constructStarSystem(int seed)
{
	float randomAngle = 6.28f * 0.01f * (rand() % 100);
	Vector2 randomDir = Vector2(cos(randomAngle), sin(randomAngle));
	currentStarPosition += randomDir * (float)(FAR_AWAY_DISTANCE_SCALE * PLANET_SPRITE_SIZE);
	Star *star = createStar(seed);
	createMiniPlanets(seed, star);
	starSystemMessage();
}

void SceneConstructor::spawnEnemies(int seed, Planet *planet)
{
	srand(seed);
	int enemiesNumber = rand() % MAX_ENEMIES + MIN_ENEMIES;
	for (int i = 0; i < enemiesNumber; i++)
	{
		new EnemyShip(planet, 
			planet->getSurfaceRadius() + MIN_ORBIT + 2 * i * ORBIT_GAP + rand() % ORBIT_GAP,
			rand() % 10 * 0.628f, rand() % 2);
	}
}

Star* SceneConstructor::createStar(unsigned seed)
{
	srand(seed);
	float scale = (float)(MIN_STAR_SCALE + rand() % MAX_STAR_SCALE);
	Star *star = new Star(currentStarPosition);
	star->setScale(scale);
	star->setMass(scale * PLANET_MASS_UNIT);
	return star;
}

void SceneConstructor::createMiniPlanets(int seed, Star *star)
{
	srand(seed);
	int planetsNumber = rand() % MAX_PLANETS + MIN_PLANETS;
	int prevOrbit = 0;
	int prevSurfaceRadius = (int) star->getSurfaceRadius();
	for (int i = 0; i < planetsNumber; i++)
	{
		int speed = MIN_PLANET_SPEED + rand() % MAX_PLANET_SPEED;
		float scale = (float) (MIN_PLANET_SCALE + rand() % MAX_PLANET_SCALE);
		int curOrbit = prevOrbit + prevSurfaceRadius +
			PLANET_SPRITE_SIZE * (MAX_PLANET_SCALE + MIN_PLANET_SCALE +
			MIN_PLANET_DISTANCE_SCALE + rand() % MAX_PLANET_DISTANCE_SCALE);
		float angle = 6.28f * (rand() % 11 * 0.1f);
		float mass = scale * PLANET_MASS_UNIT;
		MiniPlanet *planet = new MiniPlanet(star, (float)curOrbit, (float)speed / 3, angle);
		planet->setScale(scale);
		planet->setMass(mass);
		
		spawnEnemies(planet->getPlanetStageSeed(), planet);

		prevOrbit = curOrbit;
		prevSurfaceRadius = (int) planet->getSurfaceRadius();
	}
}

void SceneConstructor::starSystemMessage()
{
	std::cout << "Star System initiated. There are " + std::to_string(Scene::getUnclearedPlanetsNumber()) + " planets in it." << std::endl;
}


Vector2 SceneConstructor::currentStarPosition = Vector2(0,0);

const int SceneConstructor::FAR_AWAY_DISTANCE_SCALE = 300;

const int SceneConstructor::MIN_ENEMIES = 2;
const int SceneConstructor::MAX_ENEMIES = 2;
const int SceneConstructor::MIN_ORBIT = 800;
const int SceneConstructor::ORBIT_GAP = 300;
const int SceneConstructor::MIN_PLANETS = 3;
const int SceneConstructor::MAX_PLANETS = 3;
const int SceneConstructor::PLANET_SPRITE_SIZE = 7886;
const int SceneConstructor::MIN_PLANET_DISTANCE_SCALE = 13;
const int SceneConstructor::MAX_PLANET_DISTANCE_SCALE = 1;
const int SceneConstructor::MIN_PLANET_SPEED = 1;
const int SceneConstructor::MAX_PLANET_SPEED = 1;
const int SceneConstructor::MIN_STAR_SCALE = 8;
const int SceneConstructor::MAX_STAR_SCALE = 5;
const int SceneConstructor::MIN_PLANET_SCALE = 4;
const int SceneConstructor::MAX_PLANET_SCALE = 2;
const int SceneConstructor::PLANET_MASS_UNIT = 2000;
