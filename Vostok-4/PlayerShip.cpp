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


PlayerShip::PlayerShip(Vector2 position) : Spaceship(position)
{
	Init();
}

PlayerShip::PlayerShip(Planet *planet, const float orbit) : Spaceship(planet, orbit)
{
	Init();
}

PlayerShip::~PlayerShip()
{
	for (Engine *engine : engines)
		delete engine;
	engines.clear();
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
	currentEngine->idle();
	float curTime = getLifetime();
	if (sf::Keyboard::isKeyPressed(engineKey))
	{
		currentEngine->thrust(this);
	}
	if (sf::Keyboard::isKeyPressed(rotateUpKey))
	{
		currentEngine->rotate(this, true);
	}
	if (sf::Keyboard::isKeyPressed(rotateDownKey))
	{
		currentEngine->rotate(this, false);
	}
	if (sf::Keyboard::isKeyPressed(gunKey))
	{
		tryShoot();
	}
	if (sf::Keyboard::isKeyPressed(toggleOrbitDrawingKey))
	{
		if (curTime - lastControl >= controlDelay)
		{
			std::cout << "Orbit drawing toggled" << std::endl;
			lastControl = curTime;
			isDrawingOrbits = !isDrawingOrbits;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
	{
		if (curTime - lastControl >= controlDelay)
		{
			Statistics::setCheatUsingState(true);
			std::cout << "Auto-win invoked" << std::endl;
			lastControl = curTime;
			for (auto ptr = Scene::bodies.begin(); ptr != Scene::bodies.end(); ++ptr)
			{
				Body *body = *ptr;
				if (typeid(*body) == typeid(EnemyShip))
				{
					body->setIsDestroyed(true);
				}
			}
		}
	}
	if (curTime - lastControl >= controlDelay)
	{
		lastControl = curTime;
		switchEngines();
	}
}

void PlayerShip::draw()
{
	Body::draw();
	currentEngine->updateSprite(this);
	Scene::window->draw(*(currentEngine->getSprite()));
}

void PlayerShip::Init()
{
	setupEngines();
	currentEngine = *engines.begin();
	lastControl = 0.0f;
	Scene::playerSpawnedEvent(this);
}

void PlayerShip::setupEngines()
{
	engines.push_back(new Engine(0.05f, 1.0f, "Regular", sf::Keyboard::R));
	engines.push_back(new Engine(1.0f, 1.0f, "Interplanetary", sf::Keyboard::T));
	engines.push_back(new Engine(10.0f, 1.0f, "Interstellar", sf::Keyboard::Y));
}

void PlayerShip::switchEngines()
{
	for (Engine *engine : engines)
	{
		if (sf::Keyboard::isKeyPressed(engine->getKey()))
		{
			currentEngine = engine;
			currentEngine->idle();
		}
	}
}
