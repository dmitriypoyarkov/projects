#pragma once
#include "Planet.h"

class MiniPlanet : public Planet
{
private:
	Vector2 centerObject;
	float orbit;
	float angle;
	float speed;
	float speedFactor;
	int planetStageSeed;
	
	void changeSpeedForPlayerDistance();
public:
	MiniPlanet();
	MiniPlanet(Vector2 centerObject, float orbit, float speed);
	void copyParameters(Vector2 *position, Vector2 *centerObject, float *orbit, float *angle, float *speed, float *mass) const;
	void onClick();
	void setupSpriteList() override;
	void update() override;
	static void refreshPlanetList();

	int getPlanetStageSeed();
	bool checkPlanetStageIsCleared();
	void setPlanetStageIsCleared(bool newState);
	bool planetStageIsCleared;

	static std::list<MiniPlanet *> planets;
};

