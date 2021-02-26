#include "SceneConstructor.h"
#include <iostream>
#include "EnemyShip.h"
#include "MiniPlanet.h"

Scene * SceneConstructor::constructStage(int seed)
{
	Scene *stage = new Scene();
	stage->isStage = true;
	Scene::setActiveScene(stage->id);

	Vector2 screenCenter = Vector2(Scene::SCREEN_WIDTH / 2.0f, Scene::SCREEN_HEIGHT / 2.0f);

	StagePlanet* earth = new StagePlanet(screenCenter);

	earth->setScale(1.0f);
	spawnEnemies(seed, earth);
	//EnemyShip* enemy = new EnemyShip(earth, earth->getSurfaceRadius() + 300);
	//EnemyShip* enemy1 = new EnemyShip(earth, earth->getSurfaceRadius() + 300);
	/*EnemyShip* enemy2 = new EnemyShip(earth, earth->getSurfaceRadius() + 500);
	EnemyShip* enemy3 = new EnemyShip(earth, earth->getSurfaceRadius() + 700);*/
	Camera* camera = new Camera();
	Spaceship* ship = new PlayerShip(earth, earth->getSurfaceRadius() + 100);

//	enemy->setScale(0.06f);
	//enemy1->setScale(0.06f);
	//enemy2->setScale(0.06f);
	//enemy3->setScale(0.06f);
	ship->setScale(0.06f);
	return stage;
}

Scene * SceneConstructor::constructStarSystem(int seed)
{
	Vector2 screenCenter = Vector2(Scene::SCREEN_WIDTH / 2.0f, Scene::SCREEN_HEIGHT / 2.0f);
	Scene *starSystem = new Scene();
	starSystem->isStage = false;
	if (Scene::getActiveStarSystemID() < 0)
		Scene::setActiveStarSystem(starSystem->id);
	Scene::setActiveScene(starSystem->id);
	MiniPlanet* sun = new MiniPlanet(screenCenter, 0.0f, 0.0f);
	sun->getSprite()->setColor(sf::Color::Yellow);
	MiniPlanet* earth = new MiniPlanet(sun->position, 600.0f, 5.0f);
	MiniPlanet* mars = new MiniPlanet(sun->position, 1100.0f, 7.0f);

	Camera *camera = new Camera(sun);
	
	std::cout << "Star System initiated. There are " + std::to_string(starSystem->unclearedPlanetsNumber) + " planets in it." << std::endl;
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
