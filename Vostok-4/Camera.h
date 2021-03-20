#pragma once
#include "Body.h"
class Camera : public Body
{
private:
	Vector2* destination;
	Body *objectToFollow;
	static const float smoothness;
public:
	Camera();
	Camera(Body* &objectToFollow);
	void setupSpriteList();
	void update() override;
	void updateSprite() override;

	void setObjectToFollow(Body *objectToFollow);
};

