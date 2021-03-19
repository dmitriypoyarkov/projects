#pragma once
#include <list>
#include "Camera.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Star.h"

class Scene
{
public:
	template <typename T>
	static void eraseDestroyed(std::list<T *> *items)
	{
		bool increment = true;
		bool begin = true;
		auto itemPtr = items->begin();
		T *item;
		while (true)
		{
			if (begin)
				begin = false;
			else if (increment)
				++itemPtr;
			else
				increment = true;
			if (itemPtr == items->end())
				break;
			item = *itemPtr;

			if (item->checkIsDestroyed())
			{
				item->onDestroy();
				auto ptr = items->erase(itemPtr);
				delete item;
				itemPtr = ptr;
				increment = false;
			}
		}
	}
	
	static void onDestroy();

	static void detectCollision(Body *body);
	static void processPhysics();
	static void processGraphics();
	static void manageScene();
	static void tryCreateNewStar();

	static int getNextSceneID();

	static Star *getActiveStar();
	static void setActiveStar(Star *star);

	static void playerDestroyedEvent();
	static void playerSpawnedEvent(PlayerShip *ship);
	static void enemyDestroyedEvent(Planet *planet);
	static void enemySpawnedEvent(EnemyShip *enemy);
	static void starSystemClearedEvent();
	static void miniPlanetCreatedEvent(Planet *planet, Star *star);
	static void starCreatedEvent(Star *star);
	static void starDestroyedEvent();
	static void planetClearedEvent(Planet * planet);
	static void gameOverEvent();

	static PlayerShip *getPlayer();
	static void setActiveCamera(Camera* newCamera);
	static Camera* getActiveCamera();
	static int getUnclearedPlanetsNumber();
	static void incrementUnclearedPlanetsNumber();
	static bool checkGameOver();
	static int AddBody(Body* newBody);

	static std::list<Body*> bodies;
	static sf::RenderWindow *window;

	const static int SCREEN_WIDTH;
	const static int SCREEN_HEIGHT;
private:
	Scene();
	static Camera* activeCamera;
	static PlayerShip *player;
	static Star *activeStar;
	static int enemiesNumber;
	static int unclearedPlanetsNumber;
	static bool gameOver;
	static int starsNumber;
	static bool createNewStar;
};

