#include "Planet.h"

Planet::Planet(Vector2 position) : Body(position)
{
	size = 1.0f;
	mass = 1000.0f;
}

void Planet::onCollision(Body * other) {}

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

