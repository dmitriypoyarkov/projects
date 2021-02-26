#include "Planet.h"

Planet::Planet(int type)
{
	this->type = type;
	size = 1.0f;
	mass = 1000.0f;
	isDynamic = false;
}

void Planet::onCollision(Body * other) {}

float Planet::getSurfaceRadius() const
{
	sf::FloatRect rectangle = sprite.getLocalBounds();
	return rectangle.height * scale / 2;
}

float Planet::getFirstCosmic(float orbit) const
{
	return sqrt(Body::gravityConst * mass / (orbit));
}

