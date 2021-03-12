#include "Orbit.h"
#include <iostream>
#include "MiniPlanet.h"
#include "VirtualPlanet.h"

Orbit::Orbit()
{
	orbitColor = safeColor;
}

void Orbit::virtualUpdate(Vector2 *virtualPosition, Vector2 *virtualVelocity)
{
	for (auto ptr = VirtualPlanet::virtualPlanets.begin(); ptr != VirtualPlanet::virtualPlanets.end(); ++ptr)
	{
		VirtualPlanet *planet = *ptr;
		planet->update(orbitScale);
		sf::CircleShape point;
		point.setPosition(planet->position);
		point.setRadius(50.0f);
		point.setPointCount(3);
		Scene::window->draw(point);
		Vector2 radius = planet->position - *virtualPosition;
		Vector2 normal = radius.normalized();
		if (radius.magnitude() != 0)
			*virtualVelocity += normal * planet->mass * Body::gravityConst / pow(radius.magnitude(), 2) * orbitScale;
		*virtualPosition += *virtualVelocity * orbitScale;
	}

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
	Planet *planet = ship->planet;
	Vector2 virtualPosition = Vector2(ship->position);
	Vector2 virtualVelocity = Vector2(ship->getVelocity());
	VirtualPlanet::refreshVirtualPlanets();
	for (int i = 0; i < orbitLength; i++)
	{
		sf::CircleShape point;
		point.setPosition(virtualPosition);
		point.setRadius(20.0f);
		point.setPointCount(3);
		//if (i%3 == 0)
			Scene::window->draw(point);

		virtualUpdate(&virtualPosition, &virtualVelocity);
	}
}

const int Orbit::orbitLength = 150;
const float Orbit::orbitScale = 60.0f;
const sf::Color Orbit::safeColor = sf::Color::Blue;
const sf::Color Orbit::crashColor = sf::Color::Red;
const sf::Color Orbit::flyAwayColor = sf::Color::Magenta;