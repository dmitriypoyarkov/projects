#pragma once
#include "Body.h"
#include "StagePlanet.h"


class Spaceship : public Body
{
protected:
	StagePlanet* planet;
	void tryShoot();
public:
	Spaceship();
	Spaceship(StagePlanet* planet, const float orbit);
	virtual ~Spaceship();
	void setupSpriteList() override;
	void update() override;
	Vector2 getOrbitTangent() const;
	float lastShot;

	static const float reloadTime;
	static const float gunForce;
	static const float engineForce;
	static const float engineTorque;
};

