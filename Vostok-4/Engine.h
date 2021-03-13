#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Body.h"
class Engine : public Drawable
{
public:
	Engine(std::string name = "Regular");
	Engine(float force, float torque, std::string name, sf::Keyboard::Key key);
	sf::Keyboard::Key getKey();
	std::string getName();
	
	void updateSprite(Body *body);

	void thrust(Body *body);
	void rotate(Body *body, bool clockwise);
	void idle();
	void setupSpriteList() override;
private:
	float torque;
	float force;
	std::string name;
	sf::Keyboard::Key key;
};

