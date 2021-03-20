#pragma once
#include <iostream>
#include <list>
#include "SFML/Graphics.hpp"

class Drawable
{
public:
	Drawable();
	~Drawable();
	sf::Sprite *getSprite();
	float getScale() const;
	int getLayer() const;
	void setLayer(const int newLayer);
	float getColliderSize() const;
	void setScale(const float newScale);
	static void loadSprites();
	static const std::string RES_PATH;
protected:
	virtual void setupSpriteList() = 0;
	void loadSprite(std::string spritePath);
	void setupSprite();
	int findInSpriteList(std::string name);
	void setTextureByClassSpriteType(int classSpriteType);
	void setClassSpriteType(std::string name);
	std::vector<std::string> classSpriteList;
private:
	float colliderSize;
	int layer;
	int spriteType;
	int classSpriteType;
	float scale;
//	std::list<std::string> spriteList;
	const static std::vector <std::string> spriteList;
	const static int spriteCount;
	static std::vector <sf::Texture> textures;
	sf::Texture *texture;
	sf::Sprite sprite;
};

