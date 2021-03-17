#include "Planet.h"

Planet::Planet(Vector2 position) : Body(position)
{
	size = 1.0f;
	mass = 1000.0f;
}

void Planet::onCollision(Body * other) {}

Vector2 Planet::getGravityForce(Body * body)
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

