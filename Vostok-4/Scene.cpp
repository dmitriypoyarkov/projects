#include "Scene.h"
#include <iostream>
#include "EnemyShip.h"
#include "MiniPlanet.h"

int Scene::activeSceneID = -1;
int Scene::activeStarSystemID = -1;
const int Scene::SCREEN_HEIGHT = 800;
const int Scene::SCREEN_WIDTH = 1200;
std::vector<Scene*> Scene::scenes;
sf::RenderWindow* Scene::window = nullptr;

Scene::Scene(Body *associatedBody)
{
	id = scenes.size();
	this->associatedBody = associatedBody;
	scenes.push_back(this);
	if (activeSceneID < 0)
		setActiveScene(id);
	int enemiesNumber = 0;
	int unclearedPlanetsNumber = 0;
	bool isStage = false;
	bool isCleared = false;
	activeCamera = nullptr;
}

Scene::~Scene()
{
	bodies.clear();
	std::remove(scenes.begin(), scenes.end(), this);
}

void Scene::destroy(Body * destroyedBody)
{
}

void Scene::setActiveScene(int id)
{
	activeSceneID = id;
}

int Scene::getActiveSceneID()
{
	return activeSceneID;
}

Scene* Scene::getSceneByID(int id)
{
	if (id < 0)
	{
		std::cout << "Can't get scene by id < 0" << std::endl;
		exit(1);
	}
	return scenes[id];
	//return scenes[0];
}

Scene* Scene::getActiveScene()
{
	return getSceneByID(activeSceneID);
}

int Scene::getActiveStarSystemID()
{
	return activeStarSystemID;
}

void Scene::setActiveStarSystem(int id)
{
	activeStarSystemID = id;
}

void Scene::playerDestroyedEvent()
{
	Scene *activeScene = getActiveScene();
	for (auto bodyPtr = activeScene->bodies.begin(); bodyPtr != activeScene->bodies.end(); ++bodyPtr)
	{
		Body *body = *bodyPtr;
		if (typeid(*body) == typeid(EnemyShip))
		{
			((EnemyShip *)body)->player = nullptr;
		}
	}
}

void Scene::playerSpawnedEvent(PlayerShip *player)
{
	Scene *activeScene = getActiveScene();
	for (auto bodyPtr = activeScene->bodies.begin(); bodyPtr != activeScene->bodies.end(); ++bodyPtr)
	{
		Body *body = *bodyPtr;
		if (typeid(*body) == typeid(EnemyShip))
		{
			((EnemyShip *)body)->player = player;
		}
	}
}

void Scene::enemyDestroyedEvent()
{
	Scene *activeScene = getActiveScene();
	activeScene->enemiesNumber -= 1;

	if (activeScene->isStage)
		if (activeScene->enemiesNumber == 0)
			stageClearedEvent(activeScene);
}

void Scene::enemySpawnedEvent()
{
	getActiveScene()->enemiesNumber += 1;
}

void Scene::stageClearedEvent(Scene *stage)
{
	setActiveScene(activeStarSystemID);
	if (stage->associatedBody)
		((MiniPlanet *)(stage->associatedBody))->stageIsCleared = true;
	Scene *starSystem = getSceneByID(getActiveStarSystemID());
	starSystem->unclearedPlanetsNumber -= 1;
	if (starSystem->unclearedPlanetsNumber <= 0)
	{
		starSystemClearedEvent();
	}
}

void Scene::starSystemClearedEvent()
{
	std::cout << "Star System is cleared! Congratulations!" << std::endl;
}

void Scene::miniPlanetCreatedEvent()
{
	getSceneByID(activeStarSystemID)->unclearedPlanetsNumber += 1;
}

void Scene::setActiveCamera(Camera * newCamera)
{
	activeCamera = newCamera;
}

Camera * Scene::getActiveCamera() const
{
	return activeCamera;
}

int Scene::AddBody(Body* newBody)
{
	bodies.push_back(newBody);
	int bodyID =  (int)bodies.size() - 1;

	return bodyID;
}

bool operator==(const Scene & left, const Scene & right)
{
	return left.id == right.id;
}
