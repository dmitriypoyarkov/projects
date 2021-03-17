#pragma once
#include <list>
#include "Vector2.h"
#include "MiniPlanet.h"

class VirtualPlanet
{
public:
	Vector2 position;
	float mass;

	VirtualPlanet();
	VirtualPlanet(const MiniPlanet *origin);
	~VirtualPlanet();
	void update(float scale = 1.0f);
	static void refreshVirtualPlanets();
	static std::list<VirtualPlanet *> virtualPlanets;
private:
	Vector2 centerObject;
	float orbit;
	float angle;
	float speed;
};

