#include "Camera.h"
#include "Scene.h"

Camera::Camera()
{
	setIsMaterial(false);
	destination = nullptr;
	setScale(500.0f);
	if (Scene::getActiveCamera() == nullptr)
	{
		Scene::setActiveCamera(this);
	}
}

Camera::Camera(Body * objectToFollow) : Camera()
{
	destination = &(objectToFollow->position);
}

void Camera::setupSpriteList()
{
	addToSpriteList("");
}

void Camera::update()
{
	if (destination != nullptr)
		position = *destination;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
		setScale(getScale() / 1.05f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract))
		setScale(getScale() * 1.05f);;
}

void Camera::updateSprite() {}

void Camera::setObjectToFollow(Body * objectToFollow)
{
	if (objectToFollow == nullptr)
		destination = nullptr;
	else
		destination = &(objectToFollow->position);
}
