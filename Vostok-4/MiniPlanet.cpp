#include "MiniPlanet.h"
#include <iostream>
#include "SceneConstructor.h"

//void MiniPlanet::changeSpeedForPlayerDistance()
//{
//	distanceToPlayer = 
//	if ((Scene::getPlayer()->position - position))
//}

MiniPlanet::MiniPlanet()
{
	setupSprite();
	Scene::miniPlanetCreatedEvent();
	MiniPlanet::refreshPlanetList();
	centerObject = Vector2(0, 0);
	orbit = 0.0f;
	angle = 0.0f;
	speed = 0.0f;
	speedFactor = 0.0f;
	planetStageSeed = rand()%20000;
	planetStageIsCleared = false;
}

MiniPlanet::MiniPlanet(Vector2 centerObject, float orbit, float speed) : MiniPlanet()
{
	this->centerObject = centerObject;
	this->orbit = orbit;
	this->speed = speed;

	position = centerObject + Vector2(orbit * cos(angle), orbit * sin(angle));
}

void MiniPlanet::copyParameters(Vector2 *position, Vector2 *centerObject, float *orbit, float *angle, float *speed, float *mass) const
{
	*position = this->position;
	*centerObject = this->centerObject;
	*orbit = this->orbit;
	*angle = this->angle;
	*speed = this->speed;
	*mass = this->getMass();
}

void MiniPlanet::onClick()
{
	/*if (planetStageIsCleared)
	{
		std::cout << "Stage already cleared!" << std::endl;
		return;
	}
	std::cout << "Loading stage..." << std::endl;
	Scene* stage = SceneConstructor::constructStage(planetStageSeed);
	stage->setAssociatedBody(this);
	Scene::setActiveScene(stage->getID());*/
}

void MiniPlanet::setupSpriteList()
{
	addToSpriteList(RES_PATH + "Planet1.png");
}

void MiniPlanet::update()
{
	Vector2 radiusVector = position - centerObject;
	Vector2 tangent = Vector2(radiusVector.y, -radiusVector.x);
	Vector2 tangentNorm = tangent.normalized();
	position = position + tangentNorm * speed;

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i sfMousePos = sf::Mouse::getPosition(*(Scene::window));
		sf::Vector2f worldPos = (*(Scene::window)).mapPixelToCoords(sfMousePos);
		Vector2 mousePos = Vector2(worldPos.x, worldPos.y);
		if ((position - mousePos).magnitude() < getColliderSize())
			onClick();
	}*/
}

void MiniPlanet::refreshPlanetList()
{
	planets.clear();
	Scene *activeScene = Scene::getActiveScene();
	for (auto ptr = activeScene->bodies.begin(); ptr != activeScene->bodies.end(); ++ptr)
	{
		Body *body = *ptr;
		if (typeid(*body) != typeid(MiniPlanet)) continue;

		MiniPlanet *planet = (MiniPlanet*)body;
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

std::list<MiniPlanet *> MiniPlanet::planets;
