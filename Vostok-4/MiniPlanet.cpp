#include "MiniPlanet.h"
#include <iostream>
#include "SceneConstructor.h"

MiniPlanet::MiniPlanet()
{
	setupSprite();

	Scene::miniPlanetCreatedEvent();
	centerObject = Vector2(0, 0);
	orbit = 0.0f;
	angle = 0.0f;
	speed = 0.0f;
	planetStageSeed = rand()%20000;
	setPlanetStageIsCleared(false);
}

MiniPlanet::MiniPlanet(Vector2 centerObject, float orbit, float speed) : MiniPlanet()
{
	this->centerObject = centerObject;
	this->orbit = orbit;
	this->speed = speed;

	position = centerObject + Vector2(orbit * cos(angle), orbit * sin(angle));
}

void MiniPlanet::onClick()
{
	if (planetStageIsCleared)
	{
		std::cout << "Stage already cleared!" << std::endl;
		return;
	}
	std::cout << "Loading stage..." << std::endl;
	Scene* stage = SceneConstructor::constructStage(planetStageSeed);
	stage->setAssociatedBody(this);
	Scene::setActiveScene(stage->getID());
}

void MiniPlanet::setupSpriteList()
{
	addToSpriteList(RES_PATH + "Planet-mini.png");
}

void MiniPlanet::update()
{
	Vector2 radiusVector = position - centerObject;
	Vector2 tangent = Vector2(radiusVector.y, -radiusVector.x);
	Vector2 tangentNorm = tangent.normalized();
	position = position + tangentNorm * speed;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i sfMousePos = sf::Mouse::getPosition(*(Scene::window));
		sf::Vector2f worldPos = (*(Scene::window)).mapPixelToCoords(sfMousePos);
		Vector2 mousePos = Vector2(worldPos.x, worldPos.y);
		if ((position - mousePos).magnitude() < getColliderSize())
			onClick();
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
