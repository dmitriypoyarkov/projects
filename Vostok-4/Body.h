#pragma once
#include <string>
#include <list>
#include "Drawable.h"
#include "Vector2.h"
class Body : public Drawable
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
	virtual void draw();
	virtual void onCollision(Body *other);

	int getSceneID() const;
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
	static const int WORLD_LIMIT;
	static const float controlDelay;
protected:
	void setupSpriteList() = 0;
	int getHealth() const;
	void decreaseHealth();
	void setHealthToZero();
	float getLifetime() const;
	float getAirRotationResistance() const;
	void attractTo(Body *planet);
	void attractToPlanets();
private:
	int sceneID;
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