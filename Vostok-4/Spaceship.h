#pragma once
#include "Body.h"
#include "StagePlanet.h"

class Spaceship : public Body
{
public:
	StagePlanet* planet;
	Spaceship();
	Spaceship(StagePlanet* planet, const float orbit, const float angle = 0, const bool clockwise = true);
	virtual ~Spaceship();
	void onDestroy() override;
	void setupSpriteList() override;
	void update() override;
	Vector2 getOrbitTangent() const;
	bool checkIsDrawingOrbits();
	void produceTrash();
protected:
	void tryShoot();

	float lastControl;
	bool isDrawingOrbits;
	float lastShot;

	static const float reloadTime;
	static const float gunForce;
	static const float engineForce;
	static const float engineTorque;
};

