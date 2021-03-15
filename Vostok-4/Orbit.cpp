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
		Vector2 radius = planet->position - *virtualPosition;
		Vector2 normal = radius.normalized();
		if (radius.magnitude() != 0)
			*virtualVelocity += normal * planet->mass * Body::gravityConst / pow(radius.magnitude(), 2) * orbitScale;
		planet->update(orbitScale);
	}
	Vector2 radius = Scene::getActiveStar()->getPosition() - *virtualPosition;
	Vector2 normal = radius.normalized();
	if (radius.magnitude() != 0)
		*virtualVelocity += normal * Scene::getActiveStar()->getMass() * Body::gravityConst / pow(radius.magnitude(), 2) * orbitScale;

	*virtualPosition += *virtualVelocity * orbitScale;
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
		Scene::window->draw(point);

		virtualUpdate(&virtualPosition, &virtualVelocity);
	}
}

const int Orbit::orbitLength = 400;
const float Orbit::orbitScale = 400.0f;
const sf::Color Orbit::safeColor = sf::Color::Blue;
const sf::Color Orbit::crashColor = sf::Color::Red;
const sf::Color Orbit::flyAwayColor = sf::Color::Magenta;