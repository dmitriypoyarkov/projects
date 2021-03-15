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
	this->objectToFollow = objectToFollow;
}

void Camera::setupSpriteList()
{
	classSpriteList = { "" };
}

void Camera::update()
{
	if (objectToFollow != nullptr)
		move((objectToFollow->getPosition() - getPosition()) * smoothness);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
		setScale(getScale() / 1.05f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract))
		setScale(getScale() * 1.05f);;
}

void Camera::updateSprite() {}

void Camera::setObjectToFollow(Body * objectToFollow)
{
	this->objectToFollow = objectToFollow;
}

const float Camera::smoothness = 0.8f;