#pragma once
#include <iostream>
#include <list>
#include <vector>

class Drawable
{
public:
	Drawable();
	~Drawable();
	float getScale() const;
	int getLayer() const;
	void setLayer(int newLayer);
	float getColliderSize() const;
    void setColliderSize(int colliderSize);
    std::string getSpriteName();
	void setScale(float newScale);
	static const std::string RES_PATH;
protected:
	virtual void setupSpriteList() = 0;
	int findInSpriteList(const std::string &name);
	std::vector<std::string> classSpriteList;
private:
	float colliderSize;
	int layer;
	int spriteType;
	int classSpriteType;
	float scale;
	const static std::vector <std::string> spriteList;
	const static int spriteCount;
};

