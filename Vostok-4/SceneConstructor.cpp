#include "SceneConstructor.h"
#include <iostream>
#include "EnemyShip.h"
#include "MiniPlanet.h"

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
	if (Scene::getActiveStarSystemID() < 0)
		Scene::setActiveStarSystem(starSystem->getID());
	Scene::setActiveScene(starSystem->getID());
	MiniPlanet* sun = new MiniPlanet(screenCenter, 0.0f, 0.0f);
	sun->getSprite()->setColor(sf::Color::Yellow);
	new MiniPlanet(sun->position, 600.0f, 5.0f);
	new MiniPlanet(sun->position, 1100.0f, 7.0f);

	new Camera(sun);
	
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

const int SceneConstructor::MIN_ENEMIES = 2;
const int SceneConstructor::MAX_ENEMIES = 3;
const int SceneConstructor::MIN_ORBIT = 80;
const int SceneConstructor::MAX_ORBIT = 500;
