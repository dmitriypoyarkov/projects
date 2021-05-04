#pragma once
#include "Spaceship.h"
#include "Engine.h"

class PlayerShip : public Spaceship
{
public:
	PlayerShip(Vector2 position = Vector2(0,0));
	PlayerShip(Planet *planet, const float orbit);
	~PlayerShip() override;
	void onDestroy() override;
	void update() override;
private:
	void Init();
	void setupEngines();
	std::list<Engine *> engines;
	Engine *currentEngine;
	float lastControl;
};

