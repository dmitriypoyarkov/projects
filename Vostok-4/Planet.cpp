#include "Planet.h"
#include "Scene.h"

Planet::Planet(Vector2 position) : Body(position)
{
	Planet::refreshPlanetList();
	size = 1.0f;
	mass = 1000.0f;
}

void Planet::onCollision(const Body * other) {}

void Planet::onDestroy()
{
	Planet::refreshPlanetList();
}

Vector2 Planet::getGravityForce(Body * body) const
{
	Vector2 radius = getPosition() - body->getPosition();
	Vector2 normal = radius.normalized();
	if (radius.magnitude() != 0.0f)
		return (normal * mass * gravityConst / pow(radius.magnitude(), 2));
	else
		return Vector2(0.0f, 0.0f);
}

float Planet::getSurfaceRadius()
{
	sf::FloatRect rectangle = getSprite()->getLocalBounds();
	return rectangle.height * getScale() / 2;
}

float Planet::getFirstCosmic(float orbit) const
{
	return sqrt(Body::gravityConst * mass / (orbit));
}

float Planet::getMass() const
{
	return mass;
}

void Planet::setMass(float mass)
{
	this->mass = mass;
}

void Planet::refreshPlanetList()
{
	planets.clear();
	for (Body *body : Scene::bodies)
	{
		if (typeid(*body) != typeid(Star) && typeid(*body) != typeid(MiniPlanet)) continue;

		Planet *planet = (Planet*)body;
		if (planet->checkIsDestroyed()) continue;
		planets.push_back(planet);
	}
}

std::list<Planet *> Planet::planets;