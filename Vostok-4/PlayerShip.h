#pragma once
#include "Spaceship.h"
#include "Engine.h"
class PlayerShip : public Spaceship
{
public:
	PlayerShip(Planet *planet, const float orbit);
	~PlayerShip() override;
	void onDestroy() override;
	void update() override;
	void draw() override;
private:
	void setupEngines();
	void switchEngines();
	std::list<Engine *> engines;
	Engine *currentEngine;

	static const sf::Keyboard::Key gunKey;
	static const sf::Keyboard::Key engineKey;
	static const sf::Keyboard::Key rotateUpKey;
	static const sf::Keyboard::Key rotateDownKey;
	static const sf::Keyboard::Key toggleOrbitDrawingKey;
};

