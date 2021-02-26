#pragma once
#include "Spaceship.h"
#include "Scene.h"
class Orbit
{
	Orbit();
private:
	static void virtualUpdate(const StagePlanet *virtualPlanet, Vector2 *virtualPosition, Vector2 *virtualVelocity);
	const static sf::Color safeColor;
	const static sf::Color crashColor;
	const static sf::Color flyAwayColor;
public:
	bool isDrawingOrbit;
	sf::Color orbitSafety;
	static void drawOrbit(Spaceship *ship);
	static const int orbitLength;

};

