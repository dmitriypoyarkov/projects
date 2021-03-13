#include "Spaceship.h"
#include "Bullet.h"
#include "Trash.h"

Spaceship::Spaceship() : Body()
{
	setupSprite();
	setIsDynamic(true);
	lastShot = 0.0f;
	lastControl = 0.0f;
	isDrawingOrbits = false;
	planet = nullptr;
}

Spaceship::Spaceship(Vector2 position, Vector2 velocity) : Spaceship()
{
	this->position = position;
	setVelocity(velocity);
}

Spaceship::Spaceship(Planet* planet, const float orbit, const float angle, const bool clockwise) : Spaceship()
{
	position = planet->position - Vector2(orbit * sin(angle), orbit * cos(angle));
	this->planet = planet;
	Vector2 radius = position - planet->position;
	Vector2 tangent = getOrbitTangent();
	int dir = clockwise ? 1 : -1;

	setVelocity(planet->getVelocity() + tangent * planet->getFirstCosmic(orbit) * (float)dir);
}

Spaceship::~Spaceship() {}

void Spaceship::onDestroy()
{
	produceTrash();
}

void Spaceship::setupSpriteList()
{
	addToSpriteList(RES_PATH + "Rocket1.png");
}

void Spaceship::update()
{
	Body::update();
	attractToPlanets();
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
		new Bullet(position, rotation, getVelocity() + getMovingDirection() * gunForce, this);
		lastShot = curTime;
	}
}

bool Spaceship::checkIsDrawingOrbits()
{
	return isDrawingOrbits;
}

const float Spaceship::reloadTime = 0.3f;
const float Spaceship::gunForce = 100.0f;

