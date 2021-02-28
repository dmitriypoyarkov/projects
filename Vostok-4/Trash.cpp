#include "Trash.h"

Trash::Trash() : Body()
{
	setupSprite();
	setIsDynamic(true);
}

Trash::Trash(Spaceship *origin) : Trash()
{
	originID = origin->getSceneID();
	position = origin->position;
	planet = origin->planet;
	float originSpeed = (origin->getVelocity() * 3).magnitude();
	float angle = (rand() % 10) * 0.628f;
	setVelocity(Vector2(cos(angle)*originSpeed, sin(angle)*originSpeed));
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
	setHealthToZero();
}

void Trash::setupSpriteList()
{
	addToSpriteList(RES_PATH + "Trash.png");
}
