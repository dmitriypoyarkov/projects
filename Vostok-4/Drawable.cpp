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

//void Drawable::setupSprite()
//{
//	setupSpriteList();
//	setTextureByClassSpriteType(classSpriteType);
//}

int Drawable::findInSpriteList(const std::string &name)
{
	for (int i = 0; i < spriteCount; i++)
	{
		if (spriteList[i].find(name) != std::string::npos)
		{
			return i;
		}
	}
	return 0; // sprite not found - choose first "error" sprite
}

int Drawable::getLayer() const
{
	return layer;
}

void Drawable::setLayer(int newLayer)
{
	layer = newLayer;
}

float Drawable::getScale() const
{
	return scale;
}

void Drawable::setScale(float newScale)
{
	scale = newScale;
}

float Drawable::getColliderSize() const
{
	return scale * colliderSize;
}

void Drawable::setColliderSize(int colliderSize)
{
    this->colliderSize = colliderSize;
}

std::string Drawable::getSpriteName()
{
    return classSpriteList[0];
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
	"Bullet.png"
};

const std::string Drawable::RES_PATH = "..\\resources\\";