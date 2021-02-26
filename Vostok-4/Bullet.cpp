#include "Bullet.h"

Bullet::Bullet()
{
	setupSprite();
	isDynamic = true;
}

Bullet::Bullet(Vector2 position, float rotation, Vector2 initVelocity, Body *parent) : Bullet()
{
	this->position = position;
	this->rotation = rotation;
	velocity = initVelocity;
	this->parent = parent;
}

void Bullet::onCollision(Body *other)
{
	if (other != parent)
		health = 0;
}

void Bullet::setupSpriteList()
{
	spriteList[0] = RES_PATH + "Bullet.png";
}
