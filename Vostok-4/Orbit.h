#pragma once
#include "Spaceship.h"

class Orbit
{
	Orbit();
private:
	static void virtualUpdate(Vector2 *virtualPosition, Vector2 *virtualVelocity);
	static bool hasVirtualCollision(const Vector2 &virtualPosition, const Body *origin);
public:
	static void drawOrbit(const Spaceship *ship);
	static const int orbitLength;
	static const float orbitScale;
};

