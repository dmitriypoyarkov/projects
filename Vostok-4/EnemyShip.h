#pragma once
#include "Spaceship.h"
#include "PlayerShip.h"

class EnemyShip : public Spaceship
{
public:
	EnemyShip(StagePlanet *planet, const float orbit, const float angle = 0, const bool clockwise = true);
	~EnemyShip() override;
	void update() override;
	PlayerShip *player;

	static const float detectionDelta;
	static const float detectionRadius;
};

