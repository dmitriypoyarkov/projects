#pragma once
#include "Drawable.h"
#include "Body.h"

class Engine : public Drawable
{
public:
	Engine(std::string name = "Regular");
	Engine(float force, float torque, std::string name);
	std::string getName();
	
	void thrust(Body *body);
	void rotate(Body *body, bool clockwise);
	void idle();
	void setupSpriteList() override;
private:
	float torque;
	float force;
	std::string name;
};

