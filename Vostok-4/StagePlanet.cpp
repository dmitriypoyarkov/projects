#include "StagePlanet.h"

StagePlanet::StagePlanet() {}

StagePlanet::StagePlanet(Vector2 position) : StagePlanet()
{
	setupSprite();
	this->position = position;
}

void StagePlanet::update() {}

void StagePlanet::setupSpriteList()
{
	addToSpriteList(RES_PATH + "Planet.png");
}
