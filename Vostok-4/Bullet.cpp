#include "Bullet.h"

Bullet::Bullet(Vector2 position) : Body(position)
{
    setupSpriteList();
	setIsDynamic(true);
	parent = nullptr;
    setColliderSize(1.0f);
}

Bullet::Bullet(Vector2 position, float rotation, Vector2 initVelocity, Body *parent) : Bullet(position)
{
	setRotation(rotation);
	setVelocity(initVelocity);
	this->parent = parent;
}

void Bullet::onCollision(const Body* other)
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

Body *Bullet::getParent() const
{
	return parent;
}

void Bullet::setParent(Body* &parent)
{
	this->parent = parent;
}

void Bullet::setupSpriteList()
{
	classSpriteList = { "Bullet.png" };
}
