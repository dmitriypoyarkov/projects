#include "EnemyShip.h"
#include <iostream>
#include "Scene.h"

EnemyShip::EnemyShip(Vector2 position) : Spaceship(position)
{
	Init();
}

EnemyShip::EnemyShip(Planet *planet, float orbit, float angle, bool clockwise) : Spaceship(planet, orbit, angle, clockwise)
{
	dir = clockwise ? 1 : -1;
	Init();
}

EnemyShip::~EnemyShip()
{
}

void EnemyShip::onDestroy()
{
	Spaceship::onDestroy();
	Scene::enemyDestroyedEvent(planet);
}

void EnemyShip::update()
{
	Body::update();
	attractTo(planet);
	addTorque(getAirRotationResistance());
	if (planet != nullptr)
		setRotation(Vector2::AngleDeg(Vector2(1,0), getOrbitTangent()) + (dir == -1 ? 180 : 0));
	if (Scene::getPlayer() == nullptr) return;

	Vector2 playerVector = Scene::getPlayer()->getPosition() - getPosition();
	if (playerVector.magnitude() > detectionRadius) return;
	Vector2 toPlayerDirection = playerVector.normalized();
	Vector2 movingDirection = getMovingDirection();
	float delta = (toPlayerDirection - movingDirection).magnitude();
	if (delta < detectionDelta)
		tryShoot();
}

void EnemyShip::Init()
{
	dir = 1;
	Scene::enemySpawnedEvent(this);
    setColliderSize(1.0f);
}

const float EnemyShip::detectionDelta = 0.4f;
const float EnemyShip::detectionRadius = 1000;