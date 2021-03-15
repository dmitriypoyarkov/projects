#pragma once
#include "Body.h"
#include "Spaceship.h"
class Trash : public Body
{
public:
	Trash(Vector2 position = Vector2(0,0));
	Trash(Spaceship *origin);

	Planet *planet;
protected:
	void update() override;
	void onCollision(Body *other) override;
	void setupSpriteList() override;
private:
	int originID;
	static const float timeToLive;
};

