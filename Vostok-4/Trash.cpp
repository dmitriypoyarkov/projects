#include "Trash.h"

Trash::Trash() : Body()
{
	setupSprite();
	isDynamic = true;
}

Trash::Trash(Spaceship *origin) : Trash()
{
	originID = origin->getSceneID();
	position = origin->position;
	planet = origin->planet;
	float originSpeed = (origin->getVelocity() * 3).magnitude();
	float angle = (rand() % 10) * 0.628f;
	velocity = Vector2(cos(angle)*originSpeed, sin(angle)*originSpeed);
}

void Trash::update()
{
	Body::update();
	attractTo(planet);
	addTorque(getAirRotationResistance());
}

void Trash::onCollision(Body * other)
{
	if (typeid(*other) == typeid(Trash) && ((Trash *)other)->originID == originID) return;
	health = 0;
}

void Trash::setupSpriteList()
{
	spriteList[0] = RES_PATH + "Trash.png";
}
