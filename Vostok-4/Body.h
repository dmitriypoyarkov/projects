#pragma once
#include <string>
#include <list>
#include "Drawable.h"
#include "Vector2.h"

class Planet;

class Body : public Drawable
{
public:
	Body(Vector2 position = Vector2(0,0));
	virtual ~Body();
	virtual void onDestroy();

	void travel();
	virtual void update();
	virtual void onCollision(const Body* other);

	int getSceneID() const;
	Vector2 getPosition() const;
	void move(const Vector2 &shift);
	float getRotation() const;
	void setRotation(float rotation);
	void rotate(float angle);
	Vector2 getMovingDirection() const;
	Vector2 getVelocity() const;
	void setVelocity(const Vector2 &newVelocity);
	int getHealth() const;
	void addForce(const Vector2 &force);
	void addTorque(float torque);
	void applyForces();
	void decreaseHealth();
	void setHealthToZero();

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
	static const float controlDelay;
protected:
	float getLifetime() const;
	float getAirRotationResistance() const;
	void attractTo(const Planet* planet);
	void attractToPlanets();
private:
	int sceneID;
	int health;
	int creationTime;
	Vector2 position;
	float rotation;
	Vector2 velocity;
	float rotationSpeed;
	Vector2 instantForce;
	float instantTorque;
	bool isDestroyed;
	bool isDynamic;
	bool isMaterial;
};