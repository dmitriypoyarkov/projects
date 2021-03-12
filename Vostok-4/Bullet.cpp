#include "Bullet.h"

Bullet::Bullet() : Body()
{
	setupSprite();
	setIsDynamic(true);
	parent = nullptr;
}

Bullet::Bullet(Vector2 position, float rotation, Vector2 initVelocity, Body *parent) : Bullet()
{
	this->position = position;
	this->rotation = rotation;
	setVelocity(initVelocity);
	this->parent = parent;
}

void Bullet::onCollision(Body *other)
{
	if (other != parent)
		setHealthToZero();
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
	addToSpriteList(RES_PATH + "Bullet.png");
}
