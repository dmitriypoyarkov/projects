#include "Engine.h"

Engine::Engine(std::string name)
{
	setupSpriteList();
	setClassSpriteType(name);
	setupSprite();
	getSprite()->setOrigin(getSprite()->getOrigin() + sf::Vector2f(65.0f, 0));
	this->name = name;
	this->torque = 0.0f;
	this->force = 0.0f;
	this->key = sf::Keyboard::Key();
}

Engine::Engine(float force, float torque, std::string name, sf::Keyboard::Key key) : Engine(name)
{
	this->torque = torque;
	this->force = force;
	this->key = key;
}

sf::Keyboard::Key Engine::getKey()
{
	return key;
}

std::string Engine::getName()
{
	return name;
}

void Engine::updateSprite(Body *body)
{
	getSprite()->setPosition(body->getPosition());
	getSprite()->setRotation(body->getRotation());
	getSprite()->setScale(body->getScale(), body->getScale());
}

void Engine::thrust(Body * body)
{
	getSprite()->setColor(sf::Color::White);
	body->addForce(body->getMovingDirection() * force);
}

void Engine::rotate(Body * body, bool clockwise)
{
	body->addTorque(torque * (clockwise ? 1 : -1));
}

void Engine::idle()
{
	getSprite()->setColor(sf::Color(255,255,255,0));
}

void Engine::setupSpriteList()
{
	classSpriteList =
	{
		"Regular.png",
		"Interplanetary.png",
		"Interstellar.png"
	};
}