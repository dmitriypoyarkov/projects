#include "PlayerShip.h"
#include <iostream>
#include "Scene.h"
#include "Statistics.h"
#include "EnemyShip.h"

const sf::Keyboard::Key PlayerShip::gunKey = sf::Keyboard::Space;
const sf::Keyboard::Key PlayerShip::engineKey = sf::Keyboard::LShift;
const sf::Keyboard::Key PlayerShip::rotateUpKey = sf::Keyboard::D;
const sf::Keyboard::Key PlayerShip::rotateDownKey = sf::Keyboard::A;
const sf::Keyboard::Key PlayerShip::toggleOrbitDrawingKey = sf::Keyboard::O;

PlayerShip::PlayerShip(Planet *planet, const float orbit) : Spaceship(planet, orbit)
{
	Scene::playerSpawnedEvent(this);
}

PlayerShip::~PlayerShip()
{
	
}

void PlayerShip::onDestroy()
{
	Spaceship::onDestroy();
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
		float curTime = getLifetime();
		if (curTime - lastControl >= controlDelay)
		{
			std::cout << "Orbit drawing toggled" << std::endl;
			lastControl = curTime;
			isDrawingOrbits = !isDrawingOrbits;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
	{
		float curTime = getLifetime();
		if (curTime - lastControl >= controlDelay)
		{
			Statistics::setCheatUsingState(true);
			std::cout << "Auto-win invoked" << std::endl;
			lastControl = curTime;
			Scene *activeScene = Scene::getActiveScene();
			for (auto ptr = activeScene->bodies.begin(); ptr != activeScene->bodies.end(); ++ptr)
			{
				Body *body = *ptr;
				if (typeid(*body) == typeid(EnemyShip))
				{
					body->setIsDestroyed(true);
				}
			}
		}
	}
}