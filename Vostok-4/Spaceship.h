#pragma once
#include "Body.h"
#include "StagePlanet.h"

class Spaceship : public Body
{
protected:
	float lastControl;
	void tryShoot();
public:
	StagePlanet* planet;
	Spaceship();
	Spaceship(StagePlanet* planet, const float orbit, const float angle = 0, const bool clockwise = true);
	virtual ~Spaceship();
	void onDestroy() override;
	void setupSpriteList() override;
	void update() override;
	Vector2 getOrbitTangent() const;
	void produceTrash();

	float lastShot;
	bool drawOrbits;

	static const float reloadTime;
	static const float gunForce;
	static const float engineForce;
	static const float engineTorque;
};

