#pragma once
#include "Body.h"

class Planet : public Body
{
private:
	float size;
public:
	Planet(int type = 0);

	void onCollision(Body *other) override;

	float getSurfaceRadius() const;
	float getFirstCosmic(float orbit) const;

	float mass;
};