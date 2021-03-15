#pragma once
#include "Planet.h"
class Star : public Planet
{
public:
	Star(Vector2 position = Vector2(0,0));
	~Star();
	bool checkIsNewStar();
	void addPlanet(Planet *planet);
	void onDestroy() override;
private:
	std::list<Planet *> planets;
	bool isNewStar;
	float distanceToPlayer();
	void setupSpriteList() override;
	void update() override;
	void deletePlanets();
	static const float starSystemRadius;
};

