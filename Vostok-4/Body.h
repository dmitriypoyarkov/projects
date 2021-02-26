#pragma once
#include <string>
#include "Vector2.h"
class Body
{
protected:
	int sceneID;
	std::string spritePath;
	std::string spriteList[5];
	sf::Texture texture;
	sf::Sprite sprite;
	float scale;
	int layer;
	int type;
	Vector2 velocity;
	float rotationSpeed;
	Vector2 instantForce;
	float instantTorque;
	float colliderSize;

	float getTime();
	Vector2 getAirResistance();
	float getAirRotationResistance();
	void loadSprite(std::string spritePath);
	virtual void setupSpriteList() = 0;
	sf::Clock clock;
public:
	Body();
	Body(Vector2 position);
	virtual ~Body();
	void setupSprite();

	void travel();
	virtual void update();
	virtual void updateSprite();
	virtual void onCollision(Body *other);

	int getLayer() const;
	void setLayer(const int newLayer);
	float getScale() const;
	void setScale(const float newScale);
	sf::Sprite *getSprite();
	float getColliderSize();
	Vector2 getMovingDirection() const;

	void addForce(const Vector2 force);
	void addTorque(const float torque);
	void applyForces();


	Vector2 position;
	float rotation;
	int health;
	bool isMaterial;
	bool isDestroyed;
	bool isDynamic;

	static const float maxSpeed;
	static const float gravityConst;
	static const float degToRad;
	static const float airResistanceForce;
	static const std::string RES_PATH;
	static const int WORLD_LIMIT;
};