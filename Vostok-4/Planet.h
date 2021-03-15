#pragma once
#include "Body.h"

class Planet : public Body
{
public:
	Planet(Vector2 position = Vector2(0,0));

	void onCollision(Body *other) override;

	float getSurfaceRadius();
	float getFirstCosmic(float orbit) const;
	float getMass() const;
	void setMass(float mass);
private:
	float size;
	float mass;
};