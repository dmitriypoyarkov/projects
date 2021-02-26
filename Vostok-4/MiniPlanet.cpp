#include "MiniPlanet.h"
#include <iostream>
#include "SceneConstructor.h"

MiniPlanet::MiniPlanet(int type)
{
	this->type = type;
	setupSprite();

	Scene::miniPlanetCreatedEvent();
	centerObject = Vector2(0, 0);
	orbit = 0.0f;
	angle = 0.0f;
	speed = 0.0f;
	stageSeed = rand()%20000;
	stageIsCleared = false;
}

MiniPlanet::MiniPlanet(Vector2 centerObject, float orbit, float speed, int type) : MiniPlanet(type)
{
	this->centerObject = centerObject;
	this->orbit = orbit;
	this->speed = speed;

	position = centerObject + Vector2(orbit * cos(angle), orbit * sin(angle));
}

void MiniPlanet::onClick()
{
	std::cout << "Click!" << std::endl;
	if (stageIsCleared) return;

	Scene* stage = SceneConstructor::constructStage(stageSeed);
	stage->associatedBody = this;
	Scene::setActiveScene(stage->id);
}

void MiniPlanet::setupSpriteList()
{
	spriteList[0] = RES_PATH + "Planet-mini.png";
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
		if ((position - mousePos).magnitude() < colliderSize)
			onClick();
	}
}