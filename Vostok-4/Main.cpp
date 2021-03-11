//#include <vld.h>
#include <string>
#include <iostream>
#include "SceneConstructor.h"

void showStartMessage()
{
	std::cout << "\tVOSTOK-4" << std::endl
		<< "Click on a planet to start." << std::endl
		<< "Camera control: \"+\" and \"-\"" << std::endl
		<< "Ship control: Accelerate: LShift" << std::endl
		<< "Shoot: Space" << std::endl
		<< "Rotate: A D" <<std::endl
		<< "Enable\\disable orbit drawing: O" << std::endl;
}
void runGame()
{
	Scene::window = new sf::RenderWindow(sf::VideoMode(Scene::SCREEN_WIDTH, Scene::SCREEN_HEIGHT), "Space!");
	Scene::window->setFramerateLimit(60);
	SceneConstructor::constructStarSystem(5);

	showStartMessage();

	sf::Event event;
	while (Scene::window->isOpen())
	{
		while (Scene::window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Scene::window->close();
				Scene::destroyAllScenes();
			}
			else if (event.type == sf::Event::Resized)
				Scene::window->setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
		}
		Scene::processPhysics();
		Scene::processGraphics();
	}
	delete Scene::window;
}

int main()
{
	runGame();
	return 0;
}
