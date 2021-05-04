#include "Trash.h"

Trash::Trash(Vector2 position) : Body(position)
{
    setupSpriteList();
	originID = -1;
	planet = nullptr;
	setIsDynamic(true);
    setColliderSize(1.0f);
}

Trash::Trash(Spaceship *origin) : Trash(origin->getPosition())
{
	originID = origin->getSceneID();
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
	if (getLifetime() >= timeToLive)
		setIsDestroyed(true);
}

void Trash::onCollision(const Body* other)
{
	if (typeid(*other) == typeid(Trash) && ((Trash *)other)->originID == originID) return;
	setHealthToZero();
}

void Trash::setupSpriteList()
{
	classSpriteList = { "Trash.png" };
}
const float Trash::timeToLive = 30.0f;