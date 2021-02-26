#include "StagePlanet.h"

StagePlanet::StagePlanet() {}

StagePlanet::StagePlanet(Vector2 position, int type) : StagePlanet()
{
	this->type = type;
	setupSprite();
	this->position = position;
}

void StagePlanet::update() {}

void StagePlanet::setupSpriteList()
{
	spriteList[0] = RES_PATH + "Planet.png";
}
