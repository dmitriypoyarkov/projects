#include "Scene.h"
#include <iostream>
#include "EnemyShip.h"
#include "MiniPlanet.h"

int Scene::activeSceneID = -1;
int Scene::activeStarSystemID = -1;
const int Scene::SCREEN_HEIGHT = 800;
const int Scene::SCREEN_WIDTH = 1200;
bool Scene::sceneWasRemoved;
std::list<Scene*> Scene::scenes;
sf::RenderWindow* Scene::window = nullptr;

int Scene::getNextSceneID()
{
	static int sceneid = -1;
	sceneid += 1;
	return sceneid;
}

int Scene::getNextID()
{
	static int id = -1;
	id += 1;
	return id;
}

Scene::Scene(Body *associatedBody)
{
	id = getNextID();
	this->associatedBody = associatedBody;
	scenes.push_back(this);
	if (activeSceneID < 0)
		setActiveScene(id);
	enemiesNumber = 0;
	unclearedPlanetsNumber = 0;
	isStage = false;
	isCleared = false;
	sceneWasRemoved = false;
	activeCamera = nullptr;
}

Scene::~Scene()
{
	while (bodies.size() > 0)
	{
		bodies.erase(bodies.begin());
	}
	Scene::scenes.remove(this);
}

void Scene::onDestroy() {}

void Scene::destroy(Body * destroyedBody)
{
	destroyedBody->onDestroy();
	getActiveScene()->bodies.remove(destroyedBody);
	delete destroyedBody;
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
	for (Scene *scene : scenes)
		if (scene->id == id)
			return scene;

	std::cout << "No such scene!" << std::endl;
	return nullptr;
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
	Camera *camera = activeScene->getActiveCamera();
	camera->setObjectToFollow(nullptr);
	for (auto bodyPtr = activeScene->bodies.begin(); bodyPtr != activeScene->bodies.end(); ++bodyPtr)
	{
		Body *body = *bodyPtr;
		if (typeid(*body) == typeid(EnemyShip))
		{
			((EnemyShip *)body)->player = nullptr;
		}
	}
	gameOverEvent();
}

void Scene::playerSpawnedEvent(PlayerShip *player)
{
	Scene *activeScene = getActiveScene();
	Camera *camera = activeScene->getActiveCamera();
	camera->setObjectToFollow(player);
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
	if (activeScene == nullptr) return;
	activeScene->enemiesNumber -= 1;

	std::cout << "Enemies remained: " + std::to_string(activeScene->enemiesNumber) << std::endl;

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
	if (stage->associatedBody)
		((MiniPlanet *)(stage->associatedBody))->stageIsCleared = true;
	stage->isDestroyed = true;
	setActiveScene(activeStarSystemID);
	Scene *starSystem = getSceneByID(getActiveStarSystemID());
	starSystem->unclearedPlanetsNumber -= 1;
	std::cout << "Stage cleared! Planets remained: " + std::to_string(starSystem->unclearedPlanetsNumber) << std::endl;
	if (starSystem->unclearedPlanetsNumber <= 0)
	{
		starSystemClearedEvent();
	}
}

void Scene::starSystemClearedEvent()
{
	std::cout << "Star System is cleared! Congratulations!" << std::endl;
}

void Scene::stageEscapedEvent(Scene *stage)
{
	delete stage;
}

void Scene::miniPlanetCreatedEvent()
{
	getSceneByID(activeStarSystemID)->unclearedPlanetsNumber += 1;
}

void Scene::gameOverEvent()
{
	std::cout << "Game Over!" << std::endl;
	getActiveScene()->isDestroyed = true;
	setActiveScene(activeStarSystemID);
	Scene *activeScene = getActiveScene();
	for (auto bodyPtr = activeScene->bodies.begin(); bodyPtr != activeScene->bodies.end(); ++bodyPtr)
	{
		Body *body = *bodyPtr;
		if (typeid(*body) == typeid(MiniPlanet))
		{
			if (((MiniPlanet *)body)->stageIsCleared == true)
			{
				((MiniPlanet *)body)->stageIsCleared = false;
				activeScene->unclearedPlanetsNumber += 1;
			}
		}
	}
}

void Scene::destroyScene(Scene *scene)
{
	scenes.remove(scene);
	delete scene;
}

bool Scene::sceneWasRemovedCheck()
{
	bool initValue = sceneWasRemoved;
	sceneWasRemoved = false;
	return initValue;
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
	int bodyID = getNextSceneID();

	return bodyID;
}

bool operator==(const Scene & left, const Scene & right)
{
	return left.id == right.id;
}
