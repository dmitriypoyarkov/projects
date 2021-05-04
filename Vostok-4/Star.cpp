#include "Star.h"
#include "Scene.h"
#include "MiniPlanet.h"

Star::Star(Vector2 position) : Planet(position)
{
    setupSpriteList();
	isNewStar = true;
	setIsDynamic(false);
    setColliderSize(200.0f);
	Planet::refreshPlanetList();
	Scene::starCreatedEvent(this);
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
	Planet::onDestroy();
	deletePlanets();
}

void Star::copyParameters(Vector2 *position,
	Vector2 *centerObject,
	float *orbit,
	float *colliderSize,
	float *speed,
	float *mass) const
{
	*position = this->getPosition();
	*centerObject = this->getPosition();
	*orbit = 0.0f;
	*colliderSize = this->getColliderSize();
	*speed = 0.0f;
	*mass = this->getMass();
}

float Star::distanceToPlayer()
{
	return (getPosition() - Scene::getPlayer()->getPosition()).magnitude();
}

void Star::setupSpriteList()
{
	classSpriteList = { "Planet-mini.png" };
}

void Star::update()
{
	if (Scene::getActiveStar() == this) return;
	
	if (Scene::getPlayer() == nullptr) return;

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