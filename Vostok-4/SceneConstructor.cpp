#include "SceneConstructor.h"
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
	EnemyShip* enemy = new EnemyShip(earth, earth->getSurfaceRadius() + 300);
	//EnemyShip* enemy1 = new EnemyShip(earth, earth->getSurfaceRadius() + 300);
	/*EnemyShip* enemy2 = new EnemyShip(earth, earth->getSurfaceRadius() + 500);
	EnemyShip* enemy3 = new EnemyShip(earth, earth->getSurfaceRadius() + 700);*/
	Spaceship* ship = new PlayerShip(earth, earth->getSurfaceRadius() + 100);
	Camera* camera = new Camera(ship);
	enemy->setScale(0.06f);
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
	sun->getSprite()->setColor(sf::Color::Red);
	MiniPlanet* earth = new MiniPlanet(sun->position, 600.0f, 5);

	Camera *camera = new Camera(sun);
	
	return starSystem;
}
