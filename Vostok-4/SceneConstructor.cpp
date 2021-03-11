#include "SceneConstructor.h"
#include <iostream>
#include "EnemyShip.h"

Scene * SceneConstructor::constructStage(int seed)
{
	Scene *stage = new Scene();
	stage->setIsStage(true);
	Scene::setActiveScene(stage->getID());

	Vector2 screenCenter = Vector2(Scene::SCREEN_WIDTH / 2.0f, Scene::SCREEN_HEIGHT / 2.0f);

	StagePlanet* earth = new StagePlanet(screenCenter);

	earth->setScale(1.0f);
	spawnEnemies(seed, earth);
	new Camera();
	Spaceship* ship = new PlayerShip(earth, earth->getSurfaceRadius() + 100);

	ship->setScale(0.06f);
	return stage;
}



Scene * SceneConstructor::constructStarSystem(int seed)
{
	Vector2 screenCenter = Vector2(Scene::SCREEN_WIDTH / 2.0f, Scene::SCREEN_HEIGHT / 2.0f);
	Scene *starSystem = new Scene();
	starSystem->setIsStage(false);
	Scene::setActiveStarSystem(starSystem->getID());
	Scene::setActiveScene(starSystem->getID());
	MiniPlanet *star = createStar(seed);
	createMiniPlanets(seed, star);
	new Camera(star);
	
	std::cout << "Star System initiated. There are " + std::to_string(starSystem->getUnclearedPlanetsNumber()) + " planets in it." << std::endl;
	return starSystem;
}

void SceneConstructor::spawnEnemies(int seed, StagePlanet *planet)
{
	srand(seed);
	int enemiesNumber = rand() % MAX_ENEMIES + MIN_ENEMIES;
	std::cout << "There are " + std::to_string(enemiesNumber) + " enemies on this stage." << std::endl;
	for (int i = 0; i < enemiesNumber; i++)
	{
		EnemyShip *enemy = new EnemyShip(planet, 
			planet->getSurfaceRadius() + MIN_ORBIT + rand() % MAX_ORBIT,
			rand() % 10 * 0.628f, rand() % 2);
		enemy->setScale(0.06f);
	}
}

MiniPlanet* SceneConstructor::createStar(unsigned seed)
{
	MiniPlanet *star = new MiniPlanet(Vector2(0, 0), 0, 0);
	return star;
}

void SceneConstructor::createMiniPlanets(int seed, MiniPlanet *star)
{
	srand(seed);
	int planetsNumber = rand() % MAX_PLANETS + MIN_PLANETS;
	int prevOrbit = 0;
	int prevSurfaceRadius = (int) star->getSurfaceRadius();
	for (int i = 0; i < planetsNumber; i++)
	{
		int curOrbit = prevOrbit + prevSurfaceRadius +
			MIN_PLANET_DISTANCE + rand() % MAX_PLANET_DISTANCE;
		int speed = MIN_PLANET_SPEED + rand() % MAX_PLANET_SPEED;
		MiniPlanet *planet = new MiniPlanet(star->position, curOrbit, speed);

		prevOrbit = curOrbit;
		prevSurfaceRadius = (int) planet->getSurfaceRadius();
	}
}

const int SceneConstructor::MIN_ENEMIES = 2;
const int SceneConstructor::MAX_ENEMIES = 3;
const int SceneConstructor::MIN_ORBIT = 80;
const int SceneConstructor::MAX_ORBIT = 500;
const int SceneConstructor::MIN_PLANETS = 2;
const int SceneConstructor::MAX_PLANETS = 5;
const int SceneConstructor::MIN_PLANET_DISTANCE = 100;
const int SceneConstructor::MAX_PLANET_DISTANCE = 300;
const int SceneConstructor::MIN_PLANET_SPEED = 3;
const int SceneConstructor::MAX_PLANET_SPEED = 10;
