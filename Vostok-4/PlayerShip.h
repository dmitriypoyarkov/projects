#pragma once
#include "Spaceship.h"
class PlayerShip : public Spaceship
{
public:
	PlayerShip(StagePlanet *planet, const float orbit);
	~PlayerShip() override;
	void update() override;

private:
	static const sf::Keyboard::Key gunKey;
	static const sf::Keyboard::Key engineKey;
	static const sf::Keyboard::Key rotateUpKey;
	static const sf::Keyboard::Key rotateDownKey;
	static const sf::Keyboard::Key toggleOrbitDrawingKey;
};

