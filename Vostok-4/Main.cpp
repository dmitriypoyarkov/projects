//#include <vld.h>
#include <string>
#include <iostream>
#include "SceneConstructor.h"

void showStartMessage()
{
	std::cout << "\tVOSTOK-4" << std::endl
		<< "Press Shift to accelerate, A/D - rotate" << std::endl
		<< "Camera control: \"+\" and \"-\"" << std::endl
		<< "Ship control: Accelerate: LShift" << std::endl
		<< "Destroy everyone in this star system!" << std::endl
		<< "Use Space to shoot." << std::endl
		<< "Enable\\disable orbit drawing: O" << std::endl
		<< "Switch between engines with R, T, Y." << std::endl;
}
void runGame()
{
	Scene::window = new sf::RenderWindow(sf::VideoMode(Scene::SCREEN_WIDTH, Scene::SCREEN_HEIGHT), "Space!");
	Scene::window->setFramerateLimit(60);
	Drawable::loadSprites();
	srand(0);
	showStartMessage();
	SceneConstructor::initiateGameWithStarSystem(rand());
	
	sf::Event event;
	while (Scene::window->isOpen())
	{
		while (Scene::window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Scene::window->close();
				Scene::onDestroy();
			}
			else if (event.type == sf::Event::Resized)
				Scene::window->setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
		}
		Scene::processPhysics();
		Scene::processGraphics();
		Scene::manageScene();
	}
	delete Scene::window;
}

int main()
{
	runGame();
	return 0;
}
