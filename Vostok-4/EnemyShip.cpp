#include "EnemyShip.h"
#include <iostream>
#include "Scene.h"
EnemyShip::EnemyShip(StagePlanet *planet, const float orbit, const float angle, const bool clockwise) : Spaceship(planet, orbit, angle, clockwise)
{
	player = nullptr;
	Scene::enemySpawnedEvent();
	dir = clockwise ? 1 : -1;
}

EnemyShip::~EnemyShip()
{
}

void EnemyShip::onDestroy()
{
	Spaceship::onDestroy();
	Scene::enemyDestroyedEvent();
}

void EnemyShip::update()
{
	Spaceship::update();
	rotation = Vector2::AngleDeg(Vector2(1,0), getOrbitTangent()) + (dir == -1 ? 180 : 0);
	if (player == nullptr) return;

	Vector2 playerVector = player->position - position;
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

const float EnemyShip::detectionDelta = 0.3f;
const float EnemyShip::detectionRadius = 500;