#include "Body.h"
#include <iostream>
#include "Scene.h"
#include "Bullet.h"
Vector2 Body::getAirResistance()
{
	float forceX = -(pow(position.x, 3) / abs(position.x));
	float forceY = -(pow(position.y, 3) / abs(position.y));
	return Vector2(forceX, forceY) * airResistanceForce;
}

float Body::getAirRotationResistance()
{
	if (rotationSpeed != 0)
		return -pow(rotationSpeed, 3) / abs(rotationSpeed) * airResistanceForce;
	else
		return 0.0f;
}

void Body::loadSprite(std::string spritePath)
{
	if (!texture.loadFromFile(spritePath))
	{
		std::cout << "failed to load file from " + spritePath;
	}
	sprite.setTexture(texture);
}

Body::Body()
{
	position = Vector2(0, 0);
	velocity = Vector2(0, 0);
	rotation = 0.0f;
	health = 1;
	instantForce = Vector2(0, 0);
	instantTorque = 0.0f;
	scale = 1.0f;
	colliderSize = 0.0f;
	layer = 0;
	type = 0;
	isMaterial = true;
	isDestroyed = false;
	isDynamic = false;
	Scene* activeScene = Scene::getActiveScene();
	sceneID = activeScene->AddBody(this);
}

Body::Body(Vector2 position) : Body()
{
	this->position = position;
}

Body::~Body() {}

void Body::setupSprite()
{
	setupSpriteList();

	spritePath = spriteList[type];
	loadSprite(spritePath);
	sf::FloatRect rectangle = sprite.getLocalBounds();
	Vector2 spriteSize = Vector2(rectangle.width, rectangle.height);
	sprite.setOrigin(spriteSize / 2);

	colliderSize = spriteSize.magnitude() / (float)sqrt(2);
}

//void Body::setupSpriteList() 
//{
//	spriteList[0] = "";
//}

void Body::travel()
{
	position = position + velocity;
	rotation = rotation + rotationSpeed;
}

void Body::update()
{
	if (health <= 0)
		isDestroyed = true;
	if (position.x + position.y >= WORLD_LIMIT)
		isDestroyed = true;
}

void Body::updateSprite()
{
	sprite.setPosition(position);
	sprite.setRotation(rotation);
	sprite.setScale(scale, scale);
}

void Body::onCollision(Body * other)
{
	if (typeid(*other) == typeid(Bullet) && ((Bullet *)other)->parent == this) return;

	health -= 1;
}

int Body::getLayer() const
{
	return layer;
}

void Body::setLayer(const int newLayer)
{
	layer = newLayer;
}

float Body::getScale() const
{
	return scale;
}

void Body::setScale(const float newScale)
{
	scale = newScale;
}

sf::Sprite* Body::getSprite()
{
	return &sprite;
}

float Body::getColliderSize()
{
	return scale * colliderSize;
}

Vector2 Body::getMovingDirection() const
{
	return Vector2(cos(degToRad*rotation), sin(degToRad*rotation));
}

void Body::addForce(const Vector2 force)
{
	instantForce += force;
}

void Body::addTorque(const float torque)
{
	instantTorque += torque;
}

void Body::applyForces()
{
	velocity += instantForce;
	if (velocity.magnitude() >= maxSpeed)
	{
		velocity = velocity.normalized() * maxSpeed;
	}
	instantForce = Vector2(0, 0);
	rotationSpeed += instantTorque;
	instantTorque = 0.0f;
}

float Body::getTime()
{
	return clock.getElapsedTime().asSeconds();
}

const float Body::maxSpeed = 100;
const float Body::gravityConst = 100.0f;
const float Body::airResistanceForce = 0.01f;
const float Body::degToRad = 0.0174533f;
const std::string Body::RES_PATH = "A:\\images\\resources\\";
const int Body::WORLD_LIMIT = 40000;