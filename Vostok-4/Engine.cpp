#include "Engine.h"
#include <string>


Engine::Engine(std::string name)
{
	setupSpriteList();
	this->name = name;
	this->torque = 0.0f;
	this->force = 0.0f;
    setColliderSize(1.0f);
}

Engine::Engine(float force, float torque, std::string name) : Engine(name)
{
	this->torque = torque;
	this->force = force;
}

std::string Engine::getName()
{
	return name;
}

void Engine::thrust(Body * body)
{
	body->addForce(body->getMovingDirection() * force);
}

void Engine::rotate(Body * body, bool clockwise)
{
	body->addTorque(torque * (clockwise ? 1 : -1));
}

void Engine::idle()
{
	
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