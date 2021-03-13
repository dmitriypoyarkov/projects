#include "Body.h"
#include <iostream>
#include "Scene.h"
#include "Bullet.h"
#include "MiniPlanet.h"

float Body::getAirRotationResistance() const
{
	if (rotationSpeed != 0)
		return -pow(rotationSpeed, 3) / abs(rotationSpeed) * airResistanceForce;
	else
		return 0.0f;
}

bool Body::checkIsMaterial() const
{
	return isMaterial;
}

void Body::setIsMaterial(bool newState)
{
	isMaterial = newState;
}

void Body::attractTo(Body *bplanet)
{
	if (bplanet == nullptr)
	{
		std::cout << "Object has no planet!" << std::endl;
		return;
	}
	StagePlanet *planet = (StagePlanet *)bplanet;
	Vector2 radius = planet->position - position;
	Vector2 normal = radius.normalized();
	if (radius.magnitude() != 0)
		addForce(normal * planet->getMass() * gravityConst / pow(radius.magnitude(), 2));
}

void Body::attractToPlanets()
{
	for (auto ptr = Scene::bodies.begin(); ptr != Scene::bodies.end(); ++ptr)
	{
		Body *body = *ptr;
		if (typeid(*body) != typeid(MiniPlanet) && typeid(*body) != typeid(Star)) continue;

		Planet *planet = (Planet *) body;
		Vector2 radius = planet->position - position;
		Vector2 normal = radius.normalized();
		if (radius.magnitude() != 0)
			addForce(normal * planet->getMass() * gravityConst / pow(radius.magnitude(), 2));
	}
}

Body::Body() : Drawable()
{
	sceneID = Scene::AddBody(this);
	position = Vector2(0, 0);
	velocity = Vector2(0, 0);
	rotationSpeed = 0.0f;
	rotation = 0.0f;
	health = 2;
	instantForce = Vector2(0, 0);
	instantTorque = 0.0f;
	colliderSize = 0.0f;
	isMaterial = true;
	isDestroyed = false;
	isDynamic = false;
}

Body::Body(Vector2 position) : Body()
{
	this->position = position;
}

Body::~Body() 
{
}

void Body::onDestroy() {}

int Body::getHealth() const
{
	return health;
}

void Body::decreaseHealth()
{
	health -= 1;
}

void Body::setHealthToZero()
{
	health = 0;
}

void Body::travel()
{
	position = position + velocity;
	rotation = rotation + rotationSpeed;
}

void Body::update()
{
	if (health <= 0)
		isDestroyed = true;
	if (position.x + position.y >= WORLD_LIMIT)
		isDestroyed = true;
}

void Body::updateSprite()
{
	getSprite()->setPosition(position);
	getSprite()->setRotation(rotation);
	getSprite()->setScale(getScale(), getScale());
}

void Body::draw()
{
	updateSprite();
	Scene::window->draw(*getSprite());
}

void Body::onCollision(Body * other)
{
	if (typeid(*other) == typeid(Bullet) && ((Bullet *)other)->getParent() == this) return;

	health -= 1;
	std::string type = typeid(*this).name();
	std::cout << type + " got 1 damage" << std::endl;
}

int Body::getSceneID() const
{
	return sceneID;
}

Vector2 Body::getMovingDirection() const
{
	return Vector2(cos(degToRad*rotation), sin(degToRad*rotation));
}

Vector2 Body::getVelocity() const
{
	return velocity;
}

void Body::setVelocity(Vector2 newVelocity)
{
	velocity = newVelocity;
}

void Body::addForce(const Vector2 force)
{
	instantForce += force;
}

void Body::addTorque(const float torque)
{
	instantTorque += torque;
}

void Body::applyForces()
{
	velocity += instantForce;
	if (velocity.magnitude() >= maxSpeed)
	{
		velocity = velocity.normalized() * maxSpeed;
	}
	instantForce = Vector2(0, 0);
	rotationSpeed += instantTorque;
	instantTorque = 0.0f;
}

bool Body::checkIsDestroyed() const
{
	return isDestroyed;
}

void Body::setIsDestroyed(bool newState)
{
	isDestroyed = newState;
}

bool Body::checkIsDynamic() const
{
	return isDynamic;
}

void Body::setIsDynamic(bool newState)
{
	isDynamic = newState;
}

float Body::getLifetime() const
{
	return clock.getElapsedTime().asSeconds();
}

const float Body::controlDelay = 0.1f;
const float Body::maxSpeed = 100000;
const float Body::gravityConst = 100.0f;
const float Body::airResistanceForce = 0.5f;
const float Body::degToRad = 0.0174533f;
const int Body::WORLD_LIMIT = 1000000;