#include <string>
#include "Body.h"
#include "Scene.h"
#include "SceneConstructor.h"
#include "Orbit.h"

void destroyScene(int id)
{
	Scene* scene = Scene::getSceneByID(id);
	for (auto bodyPtr = scene->bodies.begin();
		bodyPtr != scene->bodies.end();
		++bodyPtr)
	{
		Body* body = *bodyPtr;
		delete body;
	}
}

void detectCollision(Body *body, Scene *activeScene)
{
	if (body->isMaterial == false) return;
	for (auto bodyPtr = activeScene->bodies.begin();
		bodyPtr != activeScene->bodies.end();
		++bodyPtr)
	{
		Body* other = *bodyPtr;
		if (other == body or !other->isMaterial) continue;

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

		if (item->isDestroyed)
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

void manageScene()
{

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
		if (Scene::sceneWasRemovedCheck())
		{
			goto endOfCycle;
		}
		if (!body->isDynamic) continue;

		body->applyForces();
		
		body->travel();
	}
	eraseDestroyed(&(activeScene->bodies));
	eraseDestroyed(&(Scene::scenes));

endOfCycle:;
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
			if (((PlayerShip *)body)->drawOrbits == true)
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

void runGame()
{
	Scene::window = new sf::RenderWindow(sf::VideoMode(Scene::SCREEN_WIDTH, Scene::SCREEN_HEIGHT), "Space!");
	//sf::RenderWindow window(sf::VideoMode(Scene::SCREEN_WIDTH, Scene::SCREEN_HEIGHT), "Space!");
	//window.setActive();
	Scene::window->setFramerateLimit(60);
	Scene *star = SceneConstructor::constructStarSystem(5);

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
	//destroyScene(stage.id);
	delete Scene::window;
}



int main()
{
	runGame();
	return 0;
}