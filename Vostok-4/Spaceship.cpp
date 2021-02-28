#include "Spaceship.h"
#include "Bullet.h"
#include "Trash.h"

Spaceship::Spaceship()
{
	setupSprite();
	setIsDynamic(true);
	lastShot = 0.0f;
	isDrawingOrbits = false;
}

Spaceship::Spaceship(StagePlanet* planet, const float orbit, const float angle, const bool clockwise) : Spaceship()
{
	position = planet->position - Vector2(orbit * sin(angle), orbit * cos(angle));
	this->planet = planet;
	Vector2 radius = position - planet->position;
	Vector2 tangent = getOrbitTangent();
	int dir = clockwise ? 1 : -1;
	setVelocity(tangent * planet->getFirstCosmic(orbit) * (float)dir);
}

Spaceship::~Spaceship() {}

void Spaceship::onDestroy()
{
	produceTrash();
}

void Spaceship::setupSpriteList()
{
	addToSpriteList(RES_PATH + "Rocket.png");
}

void Spaceship::update()
{
	Body::update();
	attractTo(planet);
	addTorque(getAirRotationResistance());
}

Vector2 Spaceship::getOrbitTangent() const
{
	Vector2 radius = planet->position - position;
	return Vector2(radius.y, -radius.x).normalized();
}

void Spaceship::produceTrash()
{
	int trashNumber = rand() % 2 + 2;
	for (int i = 0; i < trashNumber; i++)
		new Trash(this);
}

void Spaceship::tryShoot()
{
	float curTime = getLifetime();
	if (curTime - lastShot >= reloadTime)
	{
		Bullet *bullet = new Bullet(position, rotation, getVelocity() + getMovingDirection() * gunForce, this);
		lastShot = curTime;
	}
}

bool Spaceship::checkIsDrawingOrbits()
{
	return isDrawingOrbits;
}


const float Spaceship::reloadTime = 0.3f;
const float Spaceship::gunForce = 100.0f;
const float Spaceship::engineTorque = 0.1f;
const float Spaceship::engineForce = 0.05f;

