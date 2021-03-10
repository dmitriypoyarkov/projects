#include "Scene.h"
#include <iostream>
#include "EnemyShip.h"
#include "MiniPlanet.h"

int Scene::activeSceneID = -1;
int Scene::activeStarSystemID = -1;
const int Scene::SCREEN_HEIGHT = 800;
const int Scene::SCREEN_WIDTH = 1200;
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
	isDestroyed = false;
	isStage = false;
	isCleared = false;
	activeCamera = nullptr;
}

void Scene::detectCollision(Body *body, Scene *activeScene)
{
	if (body->checkIsMaterial() == false) return;
	for (auto bodyPtr = activeScene->bodies.begin();
		bodyPtr != activeScene->bodies.end();
		++bodyPtr)
	{
		Body* other = *bodyPtr;
		if (other == body || !other->checkIsMaterial()) continue;

		float distance = (other->position - body->position).magnitude();
		if (distance <= (other->getColliderSize() + body->getColliderSize()) / 2)
		{
			body->onCollision(other);
		}
	}
}

void Scene::processPhysics()
{
	Scene* activeScene = getActiveScene();
	for (auto bodyPtr = activeScene->bodies.begin();
		bodyPtr != activeScene->bodies.end();
		++bodyPtr)
	{
		detectCollision(*bodyPtr, activeScene);
	}

	for (auto bodyPtr = activeScene->bodies.begin();
		bodyPtr != activeScene->bodies.end();
		++bodyPtr)
	{
		Body* body = *bodyPtr;
		body->update();
		if (!body->checkIsDynamic()) continue;

		body->applyForces();

		body->travel();
	}
	eraseDestroyed(&(activeScene->bodies));
	eraseDestroyed(&(Scene::scenes));
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
			((EnemyShip *)body)->setPlayer(nullptr);
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
			((EnemyShip *)body)->setPlayer(player);
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
		((MiniPlanet *)(stage->associatedBody))->setPlanetStageIsCleared(true);
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
			if (((MiniPlanet *)body)->checkPlanetStageIsCleared() == true)
			{
				((MiniPlanet *)body)->setPlanetStageIsCleared(false);
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

void Scene::setActiveCamera(Camera * newCamera)
{
	activeCamera = newCamera;
}

Camera * Scene::getActiveCamera() const
{
	return activeCamera;
}

bool Scene::checkIsDestroyed() const
{
	return isDestroyed;
}

void Scene::setIsDestroyed(bool newState)
{
	isDestroyed = newState;
}

bool Scene::checkIsCleared() const
{
	return isCleared;
}

void Scene::setIsCleared(bool newState)
{
	isCleared = newState;
}

int Scene::getUnclearedPlanetsNumber() const
{
	return unclearedPlanetsNumber;
}

void Scene::incrementUnclearedPlanetsNumber()
{
	unclearedPlanetsNumber++;
}

int Scene::getID() const
{
	return id;
}

Body * Scene::getAssociatedBody() const
{
	return associatedBody;
}

void Scene::setAssociatedBody(Body *associatedBody)
{
	this->associatedBody = associatedBody;
}

bool Scene::checkIsStage() const
{
	return isStage;
}

void Scene::setIsStage(bool newState)
{
	isStage = newState;
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
