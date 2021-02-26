#pragma once
#include "Planet.h"

class MiniPlanet : public Planet
{
private:
	Vector2 centerObject;
	float orbit;
	float angle;
	float speed;
public:
	MiniPlanet(int type = 0);
	MiniPlanet(Vector2 centerObject, float orbit, float speed, int type = 0);

	void onClick();
	void setupSpriteList() override;
	void update() override;

	int stageSeed;
	bool stageIsCleared;

	
};

