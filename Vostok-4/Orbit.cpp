#include "Orbit.h"
#include <iostream>
Orbit::Orbit()
{
	orbitColor = safeColor;
}

void Orbit::virtualUpdate(const StagePlanet *virtualPlanet, Vector2 *virtualPosition, Vector2 *virtualVelocity)
{
	Vector2 radius = virtualPlanet->position - *virtualPosition;
	Vector2 normal = radius.normalized();
	if (radius.magnitude() != 0)
		*virtualVelocity += normal * virtualPlanet->getMass() * Body::gravityConst / pow(radius.magnitude(), 2) * 10;
	*virtualPosition += *virtualVelocity * 10;
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
	StagePlanet *planet = ship->planet;
	Vector2 virtualPosition = Vector2(ship->position);
	Vector2 virtualVelocity = Vector2(ship->getVelocity());
	for (int i = 0; i < orbitLength; i++)
	{
		sf::CircleShape point;
		point.setPosition(virtualPosition);
		point.setRadius(5.0f);
		point.setPointCount(3);
		if (i%3 == 0)
			Scene::window->draw(point);

		virtualUpdate(planet, &virtualPosition, &virtualVelocity);
		if ((virtualPosition - planet->position).magnitude() <= planet->getSurfaceRadius())
		{
			//std::cout << "WARNING: hard landing!" << std::endl;
			break;
		}
		if ((virtualPosition - planet->position).magnitude() >= 2 * planet->getSurfaceRadius())
		{
			//std::cout << "WARNING: open space!" << std::endl;
			break;
		}
	}
}

const int Orbit::orbitLength = 150;
const sf::Color Orbit::safeColor = sf::Color::Blue;
const sf::Color Orbit::crashColor = sf::Color::Red;
const sf::Color Orbit::flyAwayColor = sf::Color::Magenta;