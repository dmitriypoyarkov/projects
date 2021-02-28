#pragma once
#include "Planet.h"
class StagePlanet :
	public Planet
{
public:
	StagePlanet();
	StagePlanet(Vector2 position);

	void update() override;
	void setupSpriteList() override;
};

