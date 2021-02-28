#pragma once
#include <string>
#include <list>
#include "Vector2.h"
class Body
{
public:
	Vector2 position;
	float rotation;

	Body();
	Body(Vector2 position);
	virtual ~Body();
	virtual void onDestroy();

	void travel();
	virtual void update();
	virtual void updateSprite();
	virtual void onCollision(Body *other);

	int getSceneID() const;
	int getLayer() const;
	void setLayer(const int newLayer);
	float getScale() const;
	void setScale(const float newScale);
	sf::Sprite *getSprite();
	float getColliderSize();
	Vector2 getMovingDirection() const;
	Vector2 getVelocity() const;
	void setVelocity(Vector2 newVelocity);
	void addForce(const Vector2 force);
	void addTorque(const float torque);
	void applyForces();

	bool checkIsDestroyed() const;
	void setIsDestroyed(bool newState);
	bool checkIsDynamic() const;
	void setIsDynamic(bool newState);
	bool checkIsMaterial() const;
	void setIsMaterial(bool newState);

	static const float maxSpeed;
	static const float gravityConst;
	static const float degToRad;
	static const float airResistanceForce;
	static const std::string RES_PATH;
	static const int WORLD_LIMIT;
	static const float controlDelay;
protected:
	virtual void setupSpriteList() = 0;
	void loadSprite(std::string spritePath);
	void addToSpriteList(std::string spritePath);
	void setupSprite();
	int getHealth() const;
	void decreaseHealth();
	void setHealthToZero();
	float getLifetime() const;
	float getAirRotationResistance() const;
	void attractTo(Body *planet);
private:
	int sceneID;
	std::string spritePath;
	std::list<std::string> spriteList;
	sf::Texture texture;
	sf::Sprite sprite;
	float scale;
	int layer;
	Vector2 velocity;
	int health;
	float rotationSpeed;
	Vector2 instantForce;
	float instantTorque;
	float colliderSize;
	sf::Clock clock;
	bool isDestroyed;
	bool isDynamic;
	bool isMaterial;
};