#include "VirtualPlanet.h"
#include "Scene.h"
std::list<VirtualPlanet *> VirtualPlanet::virtualPlanets;

VirtualPlanet::VirtualPlanet()
{
	centerObject = Vector2(0,0);
	position = Vector2(0, 0);
	orbit = 0;
	angle = 0;
	speed = 0;
	mass = 1000;
	virtualPlanets.push_back(this);
}

VirtualPlanet::VirtualPlanet(const MiniPlanet *origin) : VirtualPlanet()
{
	origin->copyParameters(&position, &centerObject, &orbit, &angle, &speed, &mass);
}

VirtualPlanet::~VirtualPlanet()
{
	
}

void VirtualPlanet::update(float scale)
{
	Vector2 radiusVector = position - centerObject;
	Vector2 tangent = Vector2(radiusVector.y, -radiusVector.x);
	Vector2 tangentNorm = tangent.normalized();
	position += tangentNorm * speed * scale;
}

void VirtualPlanet::refreshVirtualPlanets()
{
	while (virtualPlanets.size() > 0)
	{
		delete *virtualPlanets.begin();
		virtualPlanets.pop_front();
	}
	for (auto ptr = MiniPlanet::planets.begin(); ptr != MiniPlanet::planets.end(); ++ptr)
	{
		if (*ptr != nullptr)
			new VirtualPlanet(*ptr);
	}

}
