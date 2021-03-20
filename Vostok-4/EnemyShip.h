#pragma once
#include "Spaceship.h"
#include "PlayerShip.h"

class EnemyShip : public Spaceship
{
public:
	EnemyShip(Vector2 position = Vector2(0, 0));
	EnemyShip(Planet *planet, float orbit, float angle = 0, bool clockwise = true);
	~EnemyShip() override;
	void onDestroy() override;
	void update() override;

	static const float detectionDelta;
	static const float detectionRadius;
private:
	void Init();
	int dir;
};

