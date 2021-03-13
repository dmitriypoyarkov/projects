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
	float getColliderSize();
	void setScale(const float newScale);

	static const std::string RES_PATH;
protected:
	virtual void setupSpriteList() = 0;
	void loadSprite(std::string spritePath);
	void addToSpriteList(std::string spritePath);
	void setupSprite();
private:
	float colliderSize;
	int layer;
	int spriteType;
	float scale;
	std::string spritePath;
	std::list<std::string> spriteList;
	sf::Texture texture;
	sf::Sprite sprite;
};

