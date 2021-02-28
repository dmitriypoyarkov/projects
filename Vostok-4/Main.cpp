#include <string>
#include <iostream>
#include "Body.h"
#include "Scene.h"
#include "SceneConstructor.h"
#include "Orbit.h"

void detectCollision(Body *body, Scene *activeScene)
{
	if (body->checkIsMaterial() == false) return;
	for (auto bodyPtr = activeScene->bodies.begin();
		bodyPtr != activeScene->bodies.end();
		++bodyPtr)
	{
		Body* other = *bodyPtr;
		if (other == body or !other->checkIsMaterial()) continue;

		float distance = (other->position - body->position).magnitude();
		if (distance <= (other->getColliderSize() + body->getColliderSize()) / 2)
		{
			body->onCollision(other);
		}
	}
}

template <typename T>
void eraseDestroyed(std::list<T *> *items)
{
	bool increment = true;
	bool begin = true;
	auto itemPtr = items->begin();
	T *item;
	while (true)
	{
		if (begin)
			begin = false;
		else if (increment)
			++itemPtr;
		else
			increment = true;
		if (itemPtr == items->end())
			break;
		item = *itemPtr;

		if (item->checkIsDestroyed())
		{
			if (typeid(*item) == typeid(Scene))
			{

			}

			item->onDestroy();
			auto ptr = items->erase(itemPtr);

			itemPtr = ptr;
			increment = false;
		}
	}
}

void processPhysics()
{
	Scene* activeScene = Scene::getActiveScene();
	for (auto bodyPtr = activeScene->bodies.begin();
		bodyPtr != activeScene->bodies.end();
		++bodyPtr)
	{
		detectCollision(*bodyPtr, activeScene);
	}

	for (auto bodyPtr = activeScene->bodies.begin();
		bodyPtr != activeScene->bodies.end();
		++bodyPtr)
	{
		Body* body = *bodyPtr;
		body->update();
		if (!body->checkIsDynamic()) continue;

		body->applyForces();
		
		body->travel();
	}
	eraseDestroyed(&(activeScene->bodies));
	eraseDestroyed(&(Scene::scenes));
}

void processGraphics(sf::RenderWindow* window)
{
	window->clear(sf::Color::Black);

	Scene* activeScene = Scene::getActiveScene();

	for (auto bodyPtr = activeScene->bodies.begin();
		bodyPtr != activeScene->bodies.end();
		++bodyPtr)
	{
		Body* body = *bodyPtr;

		body->updateSprite();
		window->draw(*(body->getSprite()));

		if (typeid(*body) == typeid(PlayerShip))
		{
			if (((PlayerShip *)body)->checkIsDrawingOrbits() == true)
				Orbit::drawOrbit(((Spaceship *)body));
		}
	}
	Camera* camera = activeScene->getActiveCamera();
	if (camera)
	{
		sf::View view = window->getView();
		view.setCenter(camera->position);
		sf::Vector2f scale = view.getSize();
		scale = Vector2(scale.x, scale.y).normalized() * camera->getScale();
		view.setSize(scale);
		window->setView(view);
	}

	window->display();
}

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
	Scene *star = SceneConstructor::constructStarSystem(5);

	showStartMessage();

	sf::Event event;
	while (Scene::window->isOpen())
	{
		while (Scene::window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Scene::window->close();
			else if (event.type == sf::Event::Resized)
				Scene::window->setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
		}
		processPhysics();
		processGraphics(Scene::window);
	}
	delete Scene::window;
}



int main()
{
	runGame();
	return 0;
}
