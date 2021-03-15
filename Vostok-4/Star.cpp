#include "Star.h"
#include "Scene.h"
#include "MiniPlanet.h"

Star::Star(Vector2 position) : Planet(position)
{
	setupSprite();
	isNewStar = true;
	setIsDynamic(false);
	MiniPlanet::refreshPlanetList();
	Scene::starCreatedEvent();
}

Star::~Star()
{
	Scene::starDestroyedEvent();
}

bool Star::checkIsNewStar()
{
	return isNewStar;
}

void Star::addPlanet(Planet * planet)
{
	planets.push_back(planet);
}

void Star::onDestroy()
{
	deletePlanets();
	MiniPlanet::refreshPlanetList();
}

float Star::distanceToPlayer()
{
	return (getPosition() - Scene::getPlayer()->getPosition()).magnitude();
}
void Star::setupSpriteList()
{
	classSpriteList = { "Planet.png" };
}

void Star::update()
{
	if (Scene::getActiveStar() == this) return;
	
	if (distanceToPlayer() <= starSystemRadius)
	{
		Scene::setActiveStar(this);
	}
}

void Star::deletePlanets()
{
	for (Planet *planet : planets)
		planet->setIsDestroyed(true);
	planets.clear();
}

const float Star::starSystemRadius = 1000000.0f;