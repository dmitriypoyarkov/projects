#include "Camera.h"
#include "Scene.h"

Camera::Camera()
{
	isMaterial = false;
	destination = nullptr;
	scale = 500.0f;
	Scene* activeScene = Scene::getActiveScene();
	if (activeScene->getActiveCamera() == nullptr)
	{
		activeScene->setActiveCamera(this);
	}
}

Camera::Camera(Body * objectToFollow) : Camera()
{
	destination = &(objectToFollow->position);
}

void Camera::setupSpriteList()
{
	spriteList[0] = "";
}

void Camera::update()
{
	if (destination != nullptr)
		position = *destination;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
		scale /= 1.05f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract))
		scale *= 1.05f;
}

void Camera::updateSprite() {}

void Camera::setObjectToFollow(Body * objectToFollow)
{
	if (objectToFollow == nullptr)
		destination = nullptr;
	else
		destination = &(objectToFollow->position);
}
