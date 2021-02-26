#include "Spaceship.h"
#include "Bullet.h"

Spaceship::Spaceship()
{
	setupSprite();
	isDynamic = true;
	lastShot = 0.0f;
	drawOrbits = false;
}

Spaceship::Spaceship(StagePlanet* planet, const float orbit, const float angle, const bool clockwise) : Spaceship()
{
	position = planet->position - Vector2(orbit * sin(angle), orbit * cos(angle));
	this->planet = planet;
	isDynamic = true;
	Vector2 radius = position - planet->position;
	Vector2 tangent = getOrbitTangent();
	int dir = clockwise ? 1 : -1;
	velocity = tangent * planet->getFirstCosmic(orbit) * (float)dir;
}

Spaceship::~Spaceship()
{
}

void Spaceship::setupSpriteList()
{
	spriteList[0] = Body::RES_PATH + "Rocket.png";
}

void Spaceship::update()
{
	Body::update();
	Vector2 radius = planet->position - position;
	Vector2 normal = radius.normalized();
	if (radius.magnitude() != 0)
		addForce(normal * planet->mass * gravityConst / pow(radius.magnitude(), 2));
	addTorque(getAirRotationResistance());
}

Vector2 Spaceship::getOrbitTangent() const
{
	Vector2 radius = planet->position - position;
	return Vector2(radius.y, -radius.x).normalized();
}

void Spaceship::tryShoot()
{
	float curTime = getTime();
	if (curTime - lastShot >= reloadTime)
	{
		Bullet *bullet = new Bullet(position, rotation, velocity + getMovingDirection() * gunForce, this);
		lastShot = curTime;
	}
}


const float Spaceship::reloadTime = 0.3f;
const float Spaceship::gunForce = 100.0f;
const float Spaceship::engineTorque = 0.1f;
const float Spaceship::engineForce = 0.05f;

