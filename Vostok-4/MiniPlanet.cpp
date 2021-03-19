#include "MiniPlanet.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "SceneConstructor.h"

MiniPlanet::MiniPlanet(Vector2 position) : Planet(position)
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

MiniPlanet::MiniPlanet(Star * centerObject, float orbit, float speed, float angle) 
	: MiniPlanet(centerObject->getPosition() + Vector2(orbit * cos(angle), orbit * sin(angle)))
{
	this->centerObject = centerObject;
	this->orbit = orbit;
	this->speed = speed;

	setTangentVelocity();
	Scene::miniPlanetCreatedEvent(this, centerObject);
}

void MiniPlanet::copyParameters(Vector2 *position, Vector2 *centerObject, float *orbit, float *angle, float *speed, float *mass) const
{
	*position = this->getPosition();
	*centerObject = this->centerObject->getPosition();
	*orbit = this->orbit;
	*angle = this->angle;
	*speed = this->speed;
	*mass = this->getMass();
}

void MiniPlanet::setupSpriteList()
{
	classSpriteList = { "Planet.png" };
}

void MiniPlanet::update()
{
	setTangentVelocity();
}

void MiniPlanet::setTangentVelocity()
{
	if (centerObject == nullptr)
		return;
	Vector2 radiusVector = getPosition() - centerObject->getPosition();
	double radius = radiusVector.magnitude();
	double deltaAngle = speed / radius;

	double newX = radiusVector.x * cos(deltaAngle) + radiusVector.y * sin(deltaAngle);
	double newY = radiusVector.y * cos(deltaAngle) - radiusVector.x * sin(deltaAngle);
	Vector2 destinationVector = Vector2((float)newX, (float)newY);
	Vector2 tangentVector = destinationVector - radiusVector;
	setVelocity(tangentVector);
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