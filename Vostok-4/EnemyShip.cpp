#include "EnemyShip.h"
#include <iostream>
#include "Scene.h"

EnemyShip::EnemyShip(Vector2 position) : Spaceship(position)
{
	Init();
}

EnemyShip::EnemyShip(Planet *planet, const float orbit, const float angle, const bool clockwise) : Spaceship(planet, orbit, angle, clockwise)
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

	setRotation(Vector2::AngleDeg(Vector2(1,0), getOrbitTangent()) + (dir == -1 ? 180 : 0));
	if (player == nullptr) return;

	Vector2 playerVector = player->getPosition() - getPosition();
	if (playerVector.magnitude() > detectionRadius) return;
	Vector2 toPlayerDirection = playerVector.normalized();
	Vector2 movingDirection = getMovingDirection();
	float delta = (toPlayerDirection - movingDirection).magnitude();
	if (delta < detectionDelta)
		tryShoot();
}

PlayerShip *EnemyShip::getPlayer()
{
	return player;
}

void EnemyShip::setPlayer(PlayerShip *player)
{
	this->player = player;
}

void EnemyShip::Init()
{
	player = nullptr;
	dir = 1;
	Scene::enemySpawnedEvent(this);
}

const float EnemyShip::detectionDelta = 0.3f;
const float EnemyShip::detectionRadius = 500;