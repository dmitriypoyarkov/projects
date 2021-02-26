#include "EnemyShip.h"
#include <iostream>
#include "Scene.h"
EnemyShip::EnemyShip(StagePlanet *planet, const float orbit) : Spaceship(planet, orbit)
{
	player = nullptr;
	Scene::enemySpawnedEvent();
}

EnemyShip::~EnemyShip()
{
	Scene::enemyDestroyedEvent();
}

void EnemyShip::update()
{
	Spaceship::update();

	rotation = Vector2::AngleDeg(Vector2(1,0), getOrbitTangent());

	std::cout << sprite.getRotation() << std::endl;
	if (player == nullptr) return;

	Vector2 playerVector = player->position - position;
	if (playerVector.magnitude() > detectionRadius) return;
	Vector2 toPlayerDirection = playerVector.normalized();
	Vector2 movingDirection = getMovingDirection();
	float delta = (toPlayerDirection - movingDirection).magnitude();
	if (delta < detectionDelta)
		tryShoot();
}

const float EnemyShip::detectionDelta = 0.3f;
const float EnemyShip::detectionRadius = 500;