#pragma once
#include <list>
#include "Camera.h"
#include "Playership.h"

class Scene
{
private:
	Camera* activeCamera;
	static int activeSceneID;
	static int activeStarSystemID;
public:
	static std::vector<Scene*> scenes;
	Scene(Body *associatedBody = nullptr);
	~Scene();
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
	void setActiveCamera(Camera* newCamera);
	Camera* getActiveCamera() const;
	friend bool operator== (const Scene &left, const Scene &right);

	int AddBody(Body* newBody);

	int id;
	Body* associatedBody;
	int enemiesNumber;
	int unclearedPlanetsNumber;
	bool isStage;
	bool isCleared;
	std::list<Body*> bodies;

	static sf::RenderWindow *window;
	const static int SCREEN_WIDTH;
	const static int SCREEN_HEIGHT;
};

