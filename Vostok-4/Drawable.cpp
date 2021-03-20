#include "Drawable.h"
#include "Vector2.h"

Drawable::Drawable()
{
	scale = 1.0f;
	layer = 0;
	spriteType = 0;
	classSpriteType = 0;
	colliderSize = 0.0f;
}

Drawable::~Drawable()
{
	classSpriteList.clear();
}

void Drawable::loadSprite(std::string spritePath)
{
	if (!texture->loadFromFile(spritePath))
	{
		std::cout << "failed to load file from " + spritePath;
	}
	sprite.setTexture(*texture);
}

void Drawable::setupSprite()
{
	setupSpriteList();
	setTextureByClassSpriteType(classSpriteType);
	sprite.setTexture(*texture);

	sf::FloatRect rectangle = sprite.getLocalBounds();
	Vector2 spriteSize = Vector2(rectangle.width, rectangle.height);
	sprite.setOrigin(spriteSize / 2);

	colliderSize = spriteSize.magnitude() / (float)sqrt(2);
}

int Drawable::findInSpriteList(std::string name)
{
	for (int i = 0; i < spriteCount; i++)
	{
		if (spriteList[i].find(name) != std::string::npos)
		{
			return i;
		}
	}
	return 0;
}

void Drawable::loadSprites()
{
	textures.resize(spriteList.size());
	std::fill(textures.begin(), textures.end(), sf::Texture());
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i].loadFromFile(RES_PATH + spriteList[i]);
	}
}

void Drawable::setTextureByClassSpriteType(int classSpriteType)
{
	if (classSpriteType >= classSpriteList.size()) return;
	std::string classSprite = classSpriteList[classSpriteType];
	int spriteIndex = findInSpriteList(classSprite);
	texture = &textures[spriteIndex];
}

void Drawable::setClassSpriteType(std::string name)
{
	for (auto ptr = classSpriteList.begin(); ptr != classSpriteList.end(); ++ptr)
	{
		if (ptr->find(name) != std::string::npos)
		{
			classSpriteType = std::distance(classSpriteList.begin(), ptr);
		}
	}
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

float Drawable::getColliderSize() const
{
	return scale * colliderSize;
}

const int Drawable::spriteCount = 12;
const std::vector <std::string> Drawable::spriteList =
{
	"Planet.png",
	"Planet4k.png",
	"Planet-mini.png",
	"Rocket.png",
	"Rocket1.png",
	"Regular.png",
	"Interplanetary.png",
	"Interstellar.png",
	"Trash.png",
	"Planet1.png",
	"",
	"Bullet.png"
};

std::vector <sf::Texture> Drawable::textures;
const std::string Drawable::RES_PATH = "..\\resources\\";