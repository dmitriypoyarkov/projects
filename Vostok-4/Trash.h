#pragma once
#include "Body.h"
#include "StagePlanet.h"
#include "Spaceship.h"
class Trash : public Body
{
public:
	Trash();
	Trash(Spaceship *origin);

	StagePlanet *planet;
protected:
	int originID;

	void update() override;
	void onCollision(Body *other) override;
	void setupSpriteList() override;
};

