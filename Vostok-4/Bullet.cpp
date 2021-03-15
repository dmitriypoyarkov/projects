#include "Bullet.h"

Bullet::Bullet(Vector2 position) : Body(position)
{
	setupSprite();
	setIsDynamic(true);
	parent = nullptr;
}

Bullet::Bullet(Vector2 position, float rotation, Vector2 initVelocity, Body *parent) : Bullet(position)
{
	setRotation(rotation);
	setVelocity(initVelocity);
	this->parent = parent;
}

void Bullet::onCollision(Body *other)
{
	if (other != parent)
		setHealthToZero();
}

void Bullet::update()
{
	Body::update();
	if (getLifetime() >= 5)
	{
		setHealthToZero();
	}
}

Body * Bullet::getParent()
{
	return parent;
}

void Bullet::setParent(Body * parent)
{
	this->parent = parent;
}

void Bullet::setupSpriteList()
{
	classSpriteList = { "Bullet.png" };
}
