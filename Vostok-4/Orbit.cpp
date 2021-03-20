#include "Orbit.h"
#include <iostream>
#include "VirtualPlanet.h"
#include "Scene.h"

Orbit::Orbit()
{
	orbitColor = safeColor;
}

void Orbit::virtualUpdate(Vector2 *virtualPosition, Vector2 *virtualVelocity)
{
	for (auto ptr = VirtualPlanet::virtualPlanets.begin(); ptr != VirtualPlanet::virtualPlanets.end(); ++ptr)
	{
		VirtualPlanet *planet = *ptr;
		Vector2 radius = planet->position - *virtualPosition;
		Vector2 normal = radius.normalized();
		if (radius.magnitude() != 0)
			*virtualVelocity += normal * planet->mass * Body::gravityConst / pow(radius.magnitude(), 2) * orbitScale;
		planet->update(orbitScale);
	}
	*virtualPosition += *virtualVelocity * orbitScale;
}

bool Orbit::hasVirtualCollision(Vector2 virtualPosition, Body *origin)
{
	for (VirtualPlanet *planet : VirtualPlanet::virtualPlanets)
	{
		float distance = (planet->position - virtualPosition).magnitude();
		float colliderSize = planet->colliderSize;
		if (distance < colliderSize * 0.5f)
			return true;
	}
	return false;
}

void Orbit::setOrbitColor(const sf::Color orbitColor)
{
	this->orbitColor = orbitColor;
}

sf::Color Orbit::getOrbitColor()
{
	return orbitColor;
}

void Orbit::drawOrbit(Spaceship * ship)
{
	Vector2 virtualPosition = Vector2(ship->getPosition());
	Vector2 virtualVelocity = Vector2(ship->getVelocity());
	VirtualPlanet::refreshVirtualPlanets();
	float pointScale = Scene::window->getView().getSize().x;
	for (int i = 0; i < orbitLength; i++)
	{
		sf::CircleShape point;
		point.setPosition(virtualPosition);
		point.setRadius(0.001f * pointScale);
		point.setPointCount(3);

		if (hasVirtualCollision(virtualPosition, ship))
		{
			point.setFillColor(crashColor);
			point.setRadius(0.004f * pointScale);
			Scene::window->draw(point);
			break;
		}
		Scene::window->draw(point);

		virtualUpdate(&virtualPosition, &virtualVelocity);
	}
}

const int Orbit::orbitLength = 400;
const float Orbit::orbitScale = 400.0f;
const sf::Color Orbit::safeColor = sf::Color::Blue;
const sf::Color Orbit::crashColor = sf::Color::Red;
const sf::Color Orbit::flyAwayColor = sf::Color::Magenta;