#pragma once
#include "Spaceship.h"

class Orbit
{
	Orbit();
private:
	static void virtualUpdate(Vector2 *virtualPosition, Vector2 *virtualVelocity);
	static bool hasVirtualCollision(const Vector2 &virtualPosition, const Body *origin);
	const static sf::Color safeColor;
	const static sf::Color crashColor;
	const static sf::Color flyAwayColor;
	sf::Color orbitColor;
public:
	void setOrbitColor(const sf::Color orbitColor);
	sf::Color getOrbitColor();
	static void drawOrbit(const Spaceship *ship);
	static const int orbitLength;
	static const float orbitScale;
};

