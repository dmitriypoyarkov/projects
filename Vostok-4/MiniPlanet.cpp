#include "MiniPlanet.h"
#include <iostream>
#include "SceneConstructor.h"

MiniPlanet::MiniPlanet() : Planet()
{
	setupSprite();
	MiniPlanet::refreshPlanetList();
	centerObject = nullptr;
	orbit = 0.0f;
	angle = 0.0f;
	speed = 0.0f;
	speedFactor = 0.0f;
	planetStageSeed = rand()%20000;
	planetStageIsCleared = false;
	setIsDynamic(true);
}

MiniPlanet::MiniPlanet(Star * centerObject, float orbit, float speed, float angle) : MiniPlanet()
{
	this->centerObject = centerObject;
	this->orbit = orbit;
	this->speed = speed;

	position = centerObject->position + Vector2(orbit * cos(angle), orbit * sin(angle));
	setTangentVelocity();

	Scene::miniPlanetCreatedEvent(this, centerObject);
}

void MiniPlanet::copyParameters(Vector2 *position, Vector2 *centerObject, float *orbit, float *angle, float *speed, float *mass) const
{
	*position = this->position;
	*centerObject = this->centerObject->position;
	*orbit = this->orbit;
	*angle = this->angle;
	*speed = this->speed;
	*mass = this->getMass();
}

void MiniPlanet::onClick()
{
}

void MiniPlanet::setupSpriteList()
{
	addToSpriteList(RES_PATH + "Planet1.png");
}



void MiniPlanet::update()
{
	setTangentVelocity();
}

void MiniPlanet::setTangentVelocity()
{
	Vector2 radiusVector = position - centerObject->position;
	Vector2 tangent = Vector2(radiusVector.y, -radiusVector.x);
	Vector2 tangentNorm = tangent.normalized();
	setVelocity(tangentNorm * speed);
}

void MiniPlanet::refreshPlanetList()
{
	planets.clear();
	for (auto ptr = Scene::bodies.begin(); ptr != Scene::bodies.end(); ++ptr)
	{
		Body *body = *ptr;
		if (typeid(*body) != typeid(MiniPlanet)) continue;
		
		MiniPlanet *planet = (MiniPlanet*)body;
		if (planet->checkIsDestroyed()) continue;
		planets.push_back(planet);
	}
}

int MiniPlanet::getPlanetStageSeed()
{
	return planetStageSeed;
}

bool MiniPlanet::checkPlanetStageIsCleared()
{
	return planetStageIsCleared;
}

void MiniPlanet::setPlanetStageIsCleared(bool newState)
{
	planetStageIsCleared = newState;
}

void MiniPlanet::incrementEnemyCount()
{
	enemyCount++;
}

void MiniPlanet::decrementEnemyCount()
{
	enemyCount--;
	if (enemyCount <= 0)
		Scene::planetClearedEvent(this);
}

std::list<MiniPlanet *> MiniPlanet::planets;
