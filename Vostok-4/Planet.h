#pragma once
#include "Body.h"

class Planet : public Body
{
public:
	Planet(Vector2 position = Vector2(0,0));

	void onCollision(const Body* other) override;
	void onDestroy() override;

	Vector2 getGravityForce(Body *body) const;
	float getSurfaceRadius();
	float getFirstCosmic(float orbit) const;
	float getMass() const;
	void setMass(float mass);

	virtual void copyParameters(Vector2 *position, Vector2 *centerObject, float *orbit, float *colliderSize, float *speed, float *mass) const = 0;
	static void refreshPlanetList();

	static std::list<Planet *> planets;
private:
	float size;
	float mass;
};