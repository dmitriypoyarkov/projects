#include "PlayerShip.h"
#include <iostream>
#include "Scene.h"

const sf::Keyboard::Key PlayerShip::gunKey = sf::Keyboard::Space;
const sf::Keyboard::Key PlayerShip::engineKey = sf::Keyboard::LShift;
const sf::Keyboard::Key PlayerShip::rotateUpKey = sf::Keyboard::D;
const sf::Keyboard::Key PlayerShip::rotateDownKey = sf::Keyboard::A;
const sf::Keyboard::Key PlayerShip::toggleOrbitDrawingKey = sf::Keyboard::O;

PlayerShip::PlayerShip(StagePlanet *planet, const float orbit) : Spaceship(planet, orbit)
{
	Scene::playerSpawnedEvent(this);
}

PlayerShip::~PlayerShip()
{
	Scene::playerDestroyedEvent();
}

void PlayerShip::update()
{
	Spaceship::update();
	Vector2 movingDirection = getMovingDirection();
	if (sf::Keyboard::isKeyPressed(engineKey))
	{
		addForce(movingDirection * engineForce);
	}
	if (sf::Keyboard::isKeyPressed(rotateUpKey))
	{
		addTorque(engineTorque);
	}
	if (sf::Keyboard::isKeyPressed(rotateDownKey))
	{
		addTorque(-engineTorque);
	}
	if (sf::Keyboard::isKeyPressed(gunKey))
	{
		tryShoot();
	}
	if (sf::Keyboard::isKeyPressed(toggleOrbitDrawingKey))
	{
		float curTime = getTime();
		if (curTime - lastControl >= controlDelay)
		{
			std::cout << "Orbit drawing toggled" << std::endl;
			lastControl = curTime;
			drawOrbits = !drawOrbits;
		}
	}
}