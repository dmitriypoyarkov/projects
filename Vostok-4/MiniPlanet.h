#pragma once
#include "Planet.h"

class MiniPlanet : public Planet
{
private:
	Vector2 centerObject;
	float orbit;
	float angle;
	float speed;
	int planetStageSeed;
public:
	MiniPlanet();
	MiniPlanet(Vector2 centerObject, float orbit, float speed);

	void onClick();
	void setupSpriteList() override;
	void update() override;

	int getPlanetStageSeed();
	bool checkPlanetStageIsCleared();
	void setPlanetStageIsCleared(bool newState);
	bool planetStageIsCleared;
};

