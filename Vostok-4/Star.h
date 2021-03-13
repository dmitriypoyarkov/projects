#pragma once
#include "Planet.h"
class Star : public Planet
{
public:
	Star();
	Star(Vector2 position);
	bool checkIsNewStar();
	void addPlanet(Planet *planet);
	void onDestroy() override;
private:
	std::list<Planet *> planets;
	bool isNewStar;
	float distanceToPlayer();
	void setupSpriteList();
	void update() override;
	void deletePlanets();
	static const float starSystemRadius;
};

