#pragma once
#include "Body.h"

class Bullet : public Body
{
public:
	Bullet();
	Bullet(Vector2 position, float rotation, Vector2 initVelocity, Body *parent);
	void onCollision(Body *other) override;
	Body *parent;
private:
	void setupSpriteList() override;
};

