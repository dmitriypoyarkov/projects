#pragma once
#include "Spaceship.h"
#include "PlayerShip.h"

class EnemyShip : public Spaceship
{
private:
	int dir;
	PlayerShip *player;
public:
	EnemyShip(Planet *planet, const float orbit, const float angle = 0, const bool clockwise = true);
	~EnemyShip() override;
	void onDestroy() override;
	void update() override;

	PlayerShip *getPlayer();
	void setPlayer(PlayerShip *player);

	static const float detectionDelta;
	static const float detectionRadius;
};

