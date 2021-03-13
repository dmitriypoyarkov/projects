#include "Drawable.h"
#include "Vector2.h"

Drawable::Drawable()
{
	scale = 1.0f;
	layer = 0;
	spriteType = 0;
}

Drawable::~Drawable()
{
	spriteList.clear();
}

void Drawable::addToSpriteList(std::string spritePath)
{
	spriteList.push_back(spritePath);
}

void Drawable::loadSprite(std::string spritePath)
{
	if (!texture.loadFromFile(spritePath))
	{
		std::cout << "failed to load file from " + spritePath;
	}
	sprite.setTexture(texture);
}

void Drawable::setupSprite()
{
	setupSpriteList();
	auto spritePtr = spriteList.begin();
	std::advance(spritePtr, spriteType);
	spritePath = *spritePtr;
	loadSprite(spritePath);
	sf::FloatRect rectangle = sprite.getLocalBounds();
	Vector2 spriteSize = Vector2(rectangle.width, rectangle.height);
	sprite.setOrigin(spriteSize / 2);

	colliderSize = spriteSize.magnitude() / (float)sqrt(2);
}

int Drawable::getLayer() const
{
	return layer;
}

void Drawable::setLayer(const int newLayer)
{
	layer = newLayer;
}

float Drawable::getScale() const
{
	return scale;
}

void Drawable::setScale(const float newScale)
{
	scale = newScale;
}

sf::Sprite* Drawable::getSprite()
{
	return &sprite;
}

float Drawable::getColliderSize()
{
	return scale * colliderSize;
}

std::list<std::string> spriteList;
const std::string Drawable::RES_PATH = "resources\\";