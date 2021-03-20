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
	void setLayer(int newLayer);
	float getColliderSize() const;
	void setScale(float newScale);
	static void loadSprites();
	static const std::string RES_PATH;
protected:
	virtual void setupSpriteList() = 0;
	void setupSprite();
	int findInSpriteList(const std::string &name);
	void setTextureByClassSpriteType(int classSpriteType);
	void setClassSpriteType(const std::string &name);
	std::vector<std::string> classSpriteList;
private:
	float colliderSize;
	int layer;
	int spriteType;
	int classSpriteType;
	float scale;
	const static std::vector <std::string> spriteList;
	const static int spriteCount;
	static std::vector <sf::Texture> textures;
	sf::Texture *texture;
	sf::Sprite sprite;
};

