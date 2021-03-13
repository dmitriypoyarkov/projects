#include "Engine.h"



Engine::Engine(std::string name)
{
	this->name = name;
	setupSprite();
	getSprite()->setOrigin(getSprite()->getOrigin() + sf::Vector2f(65.0f, 0));
	this->torque = 0;
	this->force = 0;
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
	getSprite()->setPosition(body->position);
	getSprite()->setRotation(body->rotation);
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
	addToSpriteList(RES_PATH + name + ".png");
}
