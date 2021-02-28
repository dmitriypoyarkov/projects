#pragma once
#include "Body.h"

class Planet : public Body
{
public:
	Planet();

	void onCollision(Body *other) override;

	float getSurfaceRadius();
	float getFirstCosmic(float orbit) const;
	float getMass() const;
private:
	float size;
	float mass;
};