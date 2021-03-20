#include "VirtualPlanet.h"
#include "Scene.h"

std::list<VirtualPlanet *> VirtualPlanet::virtualPlanets;

VirtualPlanet::VirtualPlanet()
{
	centerObject = Vector2(0,0);
	position = Vector2(0, 0);
	orbit = 0;
	speed = 0;
	mass = 1000;
	colliderSize = 0.0f;
	virtualPlanets.push_back(this);
}

VirtualPlanet::VirtualPlanet(const Planet *origin) : VirtualPlanet()
{
	origin->copyParameters(&position, &centerObject, &orbit, &colliderSize, &speed, &mass);
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
	for (VirtualPlanet *virtualPlanet : virtualPlanets)
	{
		delete virtualPlanet;
	}
	virtualPlanets.clear();
	for (Planet *planet : Planet::planets)
	{
		if (planet != nullptr)
			new VirtualPlanet(planet);
	}

}
