#pragma once
#include "Body.h"

class Bullet : public Body
{
public:
	Bullet(Vector2 position = Vector2(0,0));
	Bullet(Vector2 position, float rotation, Vector2 initVelocity, Body *parent);
	void onCollision(const Body* other) override;
	void update() override;
	Body *getParent() const;
	void setParent(Body* &parent);
private:
	Body *parent;
	void setupSpriteList() override;
};

