#include "Scene.h"
#include <iostream>
#include "EnemyShip.h"
#include "MiniPlanet.h"
#include "Orbit.h"
#include "SceneConstructor.h"
#include "Statistics.h"
#include "UI.h"

const int Scene::SCREEN_HEIGHT = 800;
const int Scene::SCREEN_WIDTH = 1200;

PlayerShip* Scene::player = nullptr;
Star* Scene::activeStar = nullptr;
Camera* Scene::activeCamera = nullptr;

std::list<Body*> Scene::bodies;
sf::RenderWindow* Scene::window = nullptr;

int Scene::enemiesNumber = 0;
int Scene::unclearedPlanetsNumber = 0;
int Scene::starsNumber = 0;
bool Scene::gameOver = false;
bool Scene::createNewStar = false;

void Scene::detectCollision(Body *body)
{
	if (body->checkIsMaterial() == false) return;
	for (auto bodyPtr = bodies.begin();
		bodyPtr != bodies.end();
		++bodyPtr)
	{
		Body* other = *bodyPtr;
		if (other == body || !other->checkIsMaterial()) continue;

		float distance = (other->getPosition() - body->getPosition()).magnitude();
		if (distance <= (other->getColliderSize() + body->getColliderSize()) / 2)
		{
			body->onCollision(other);
		}
	}
}

void Scene::processPhysics()
{
	for (auto bodyPtr = Scene::bodies.begin();
		bodyPtr != Scene::bodies.end();
		++bodyPtr)
	{
		detectCollision(*bodyPtr);
	}

	for (auto bodyPtr = Scene::bodies.begin();
		bodyPtr != Scene::bodies.end();
		++bodyPtr)
	{
		Body* body = *bodyPtr;
		body->update();
		if (!body->checkIsDynamic()) continue;

		body->applyForces();

		body->travel();
	}
	Scene::eraseDestroyed(&(Scene::bodies));
}

void Scene::processGraphics()
{

	window->clear(sf::Color::Black);
	for (auto bodyPtr = Scene::bodies.begin();
		bodyPtr != Scene::bodies.end();
		++bodyPtr)
	{
		Body* body = *bodyPtr;
		body->draw();

		if (typeid(*body) == typeid(PlayerShip))
		{
			if (((PlayerShip *)body)->checkIsDrawingOrbits() == true)
				Orbit::drawOrbit(((Spaceship *)body));
		}
		UI::draw();
	}
	Camera* camera = Scene::getActiveCamera();
	if (camera)
	{
		sf::View view = window->getView();
		view.setCenter(camera->getPosition());
		sf::Vector2f scale = view.getSize();
		scale = Vector2(scale.x, scale.y).normalized() * camera->getScale();
		view.setSize(scale);
		window->setView(view);
	}

	window->display();
}

void Scene::tryCreateNewStar()
{
	if (createNewStar && starsNumber == 1)
	{
		SceneConstructor::constructStarSystem(rand() % 100);
		createNewStar = false;
	}
}

void Scene::onDestroy() 
{
	for (Body *body : bodies)
	{
		delete body;
	}
	bodies.clear();
	player = nullptr;
	activeStar = nullptr;
	activeCamera = nullptr;
	enemiesNumber = 0;
	unclearedPlanetsNumber = 0;
}

int Scene::getNextSceneID()
{
	static int sceneid = -1;
	sceneid += 1;
	return sceneid;
}

Star * Scene::getActiveStar()
{
	return activeStar;
}

void Scene::setActiveStar(Star *star)
{
	if (activeStar != nullptr)
		activeStar->setIsDestroyed(true);
	activeStar = star;
}

void Scene::playerDestroyedEvent()
{
	Camera *camera = Scene::getActiveCamera();
	camera->setObjectToFollow(nullptr);
	for (auto bodyPtr = Scene::bodies.begin(); bodyPtr != Scene::bodies.end(); ++bodyPtr)
	{
		Body *body = *bodyPtr;
		if (typeid(*body) == typeid(EnemyShip))
		{
			((EnemyShip *)body)->setPlayer(nullptr);
		}
	}
	gameOver = true;
}

void Scene::playerSpawnedEvent(PlayerShip *player)
{
	Camera *camera = Scene::getActiveCamera();
	Scene::player = player;
	if (camera != nullptr)
		camera->setObjectToFollow(player);
	for (auto bodyPtr = Scene::bodies.begin(); bodyPtr != Scene::bodies.end(); ++bodyPtr)
	{
		Body *body = *bodyPtr;
		if (typeid(*body) == typeid(EnemyShip))
		{
			((EnemyShip *)body)->setPlayer(player);
		}
	}
}

void Scene::enemyDestroyedEvent(Planet *planet)
{
	Statistics::addDestroyedEnemy();
	Scene::enemiesNumber--;
	((MiniPlanet *)planet)->decrementEnemyCount();
	std::cout << "Total enemies remained: " + std::to_string(Scene::enemiesNumber) << std::endl;
}

void Scene::enemySpawnedEvent(Planet *planet)
{
	((MiniPlanet *)planet)->incrementEnemyCount();
	enemiesNumber += 1;
}

void Scene::starSystemClearedEvent()
{
	Statistics::addClearedStarSystem();

	std::cout << "Star System is cleared! Congratulations!" << std::endl;
	std::cout << "You may now press Y to activate interstellar engine." << std::endl;
	createNewStar = true;
	tryCreateNewStar();
}

void Scene::miniPlanetCreatedEvent(Planet *planet, Star *star)
{
	unclearedPlanetsNumber += 1;
	star->addPlanet(planet);
}

void Scene::planetClearedEvent(Planet * planet)
{
	Statistics::addClearedStage();

	std::cout << "Planet cleared. Press T to activate interplanetary engine." << std::endl;
	unclearedPlanetsNumber--;
	if (unclearedPlanetsNumber <= 0)
		starSystemClearedEvent();
}

void Scene::starCreatedEvent()
{
	starsNumber++;
}

void Scene::starDestroyedEvent()
{
	starsNumber--;
	if (createNewStar)
		tryCreateNewStar();
}

void Scene::gameOverEvent()
{
	Statistics::show();
	Statistics::reset();
	std::cout << "Game Over!" << std::endl;
	Scene::onDestroy();

	SceneConstructor::initiateGameWithStarSystem(rand());
	gameOver = false;
}

PlayerShip *Scene::getPlayer()
{
	return player;
}

void Scene::setActiveCamera(Camera * newCamera)
{
	activeCamera = newCamera;
}

Camera * Scene::getActiveCamera()
{
	return Scene::activeCamera;
}

int Scene::getUnclearedPlanetsNumber()
{
	return unclearedPlanetsNumber;
}

void Scene::incrementUnclearedPlanetsNumber()
{
	unclearedPlanetsNumber++;
}

bool Scene::checkGameOver()
{
	return gameOver;
}

int Scene::AddBody(Body* newBody)
{
	bodies.push_back(newBody);
	int bodyID = Scene::getNextSceneID();

	return bodyID;
}
