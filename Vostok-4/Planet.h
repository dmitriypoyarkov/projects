#pragma once
#include "Body.h"

class Planet : public Body
{
private:
	float size;
public:
	Planet(int type = 0);

	float getSurfaceRadius() const;
	float getFirstCosmic(float orbit) const;

	float mass;
};