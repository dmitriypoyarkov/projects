#pragma once
#include "Star.h"

class MiniPlanet : public Planet
{
private:
	Star *centerObject;
	float orbit;
	float speed;
	float speedFactor;
	int planetStageSeed;
	int enemyCount;
public:
	MiniPlanet(Vector2 position = Vector2(0,0));
	MiniPlanet(Star * centerObject, float orbit, float speed = 0, float angle = 0);

	void copyParameters(Vector2 *position,
						Vector2 *centerObject,
						float *orbit,
						float *colliderSize,
						float *speed,
						float *mass) const override;
	void setupSpriteList() override;
	void update() override;
	void setTangentVelocity();

	int getPlanetStageSeed();
	bool checkPlanetStageIsCleared();
	void setPlanetStageIsCleared(bool newState);
	void incrementEnemyCount();
	void decrementEnemyCount();

	bool planetStageIsCleared;
};