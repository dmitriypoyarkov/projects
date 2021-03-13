#include "Star.h"
#include "Scene.h"
#include "MiniPlanet.h"
Star::Star()
{
	setupSprite();
	isNewStar = true;
	setIsDynamic(false);
	MiniPlanet::refreshPlanetList();
}

Star::Star(Vector2 position) : Star()
{
	this->position = position;
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
	return (position - Scene::getPlayer()->position).magnitude();
}

void Star::setupSpriteList()
{
	addToSpriteList(RES_PATH + "Planet1.png");
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

const float Star::starSystemRadius = 200000.0f;