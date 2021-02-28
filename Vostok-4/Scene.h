#pragma once
#include <list>
#include "Camera.h"
#include "PlayerShip.h"

class Scene
{
public:
	static std::list<Scene*> scenes;
	Scene(Body *associatedBody = nullptr);
	~Scene();
	void onDestroy();
	static void destroy(Body *body);
	static void setActiveScene(int id);
	static int getActiveSceneID();
	static Scene* getSceneByID(int id);
	static Scene* getActiveScene();
	static int getActiveStarSystemID();
	static void setActiveStarSystem(int id);

	static void playerDestroyedEvent();
	static void playerSpawnedEvent(PlayerShip *ship);
	static void enemyDestroyedEvent();
	static void enemySpawnedEvent();
	static void stageClearedEvent(Scene *stage);
	static void starSystemClearedEvent();
	static void miniPlanetCreatedEvent();
	static void gameOverEvent();
	static void destroyScene(Scene *scene);
	void setActiveCamera(Camera* newCamera);
	Camera* getActiveCamera() const;
	bool checkIsDestroyed() const;
	void setIsDestroyed(bool newState);
	bool checkIsStage() const;
	void setIsStage(bool newState);
	bool checkIsCleared() const;
	void setIsCleared(bool newState);
	int getUnclearedPlanetsNumber() const;
	void incrementUnclearedPlanetsNumber();
	int getID() const;
	Body *getAssociatedBody() const;
	void setAssociatedBody(Body *associatedBody);
	int AddBody(Body* newBody);
	friend bool operator== (const Scene &left, const Scene &right);

	std::list<Body*> bodies;

	static sf::RenderWindow *window;
	const static int SCREEN_WIDTH;
	const static int SCREEN_HEIGHT;
private:
	int id;
	Camera* activeCamera;
	bool isStage;
	bool isCleared;
	bool isDestroyed;
	static int activeSceneID;
	static int activeStarSystemID;
	int enemiesNumber;
	int unclearedPlanetsNumber;
	Body *associatedBody;

	int getNextSceneID();
	static int getNextID();
};

