#include "pch.h"
#include "CppUnitTest.h"

#include "../Vostok-4/Vector2.h"
#include "../Vostok-4/SceneConstructor.h"
#include "../Vostok-4/EnemyShip.h"
#include "../Vostok-4/PlayerShip.h"
#include "MiniPlanet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<> static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Vector2>(const Vector2& V)
{
	std::wstring str = L"(" + std::to_wstring(V.x) + L", " + std::to_wstring(V.y) + L")";
	return str;
}

template<> static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<sf::Vector2f>(const sf::Vector2f& V)
{
	std::wstring str = L"(" + std::to_wstring(V.x) + L", " + std::to_wstring(V.y) + L")";
	return str;
}

class T1 { int x; public: T1(int x) :x(x) {} };


/* Abstract class Body - testing on child class Spaceship */
TEST_CLASS(BodyTest)
{
public:
	TEST_METHOD(Constructors)
	{
		//Default constructor
		Spaceship *ship = new Spaceship();
		Assert::AreEqual(Vector2(0.0f, 0.0f), ship->getPosition());
		Assert::AreEqual(Vector2(0.0f, 0.0f), ship->getVelocity());
		Assert::AreEqual(0.0f, ship->getRotation());

		//Position constructor
		Vector2 expectedPosition = Vector2(-20.0f, 1000.0f);
		Spaceship *ship1 = new Spaceship(expectedPosition);
		Assert::AreEqual(expectedPosition, ship1->getPosition());
	}

	TEST_METHOD(Transforms)
	{
		//move method
		Spaceship *ship = new Spaceship();
		Vector2 initialPosition = ship->getPosition();

		Vector2 shift = Vector2(45.5, -91.2);
		ship->move(shift);
		Assert::AreEqual(initialPosition + shift, ship->getPosition());

		//rotate method
		float initialRotation = ship->getRotation();
		float rotationShift = 0.4;
		ship->rotate(rotationShift);
		Assert::AreEqual(initialRotation + rotationShift, ship->getRotation());

		Scene::onDestroy();
	}

	TEST_METHOD(Forces)
	{
		//addForce method
		Spaceship *ship = new Spaceship();
		Vector2 appliedForce = Vector2(30.0f, 20.0f);
		ship->addForce(appliedForce);
		ship->applyForces();
		Assert::AreEqual(appliedForce, ship->getVelocity());
		ship->travel();
		Assert::AreEqual(appliedForce, ship->getPosition());

		//No force added - check velocity hasn't changed
		ship->applyForces();
		Assert::AreEqual(appliedForce, ship->getVelocity());

		//addTorque method
		float addedTorque = 0.5f;
		ship->addTorque(addedTorque);
		ship->applyForces();
		ship->travel();
		Assert::AreEqual(addedTorque, ship->getRotation());
	}

	TEST_METHOD(Gravity)
	{
		//attractTo method
		MiniPlanet *planet = new MiniPlanet();
		float orbit = planet->getSurfaceRadius() + 300.0f;
		EnemyShip *ship = new EnemyShip(planet, orbit);
		ship->setVelocity(Vector2(0, 0));

		Vector2 initialPosition = ship->getPosition();
		
		Vector2 expectedShift = planet->getGravityForce(ship);
		ship->update();
		ship->applyForces();
		ship->travel();
		Assert::AreEqual(initialPosition + expectedShift, ship->getPosition());

		//attractToPlanets method
		Vector2 planetPosition1 = Vector2(4 * planet->getSurfaceRadius(), 0);
		Vector2 planetPosition2 = Vector2(0, 4 * planet->getSurfaceRadius());
		MiniPlanet *planet1 = new MiniPlanet(planetPosition1);
		MiniPlanet *planet2 = new MiniPlanet(planetPosition2);
		orbit = planet1->getSurfaceRadius() + 400.0f;
		PlayerShip *player = new PlayerShip(planet1, orbit);
		player->setVelocity(Vector2(0, 0));
		initialPosition = player->getPosition();
		//calculate expected force
		MiniPlanet* planets[] = { planet, planet1, planet2 };
		expectedShift = Vector2(0, 0);
		for (Planet *pl : planets)
		{
			expectedShift += pl->getGravityForce(player);
		}
		//proceed to test
		player->update();
		player->applyForces();
		player->travel();
		Assert::AreEqual(initialPosition + expectedShift, player->getPosition());
	}
	TEST_METHOD(Collisions)
	{
		//onCollision method
		Drawable::loadSprites(); // collider sizes depend on sprites

		PlayerShip *player = new PlayerShip();
		player->updateSprite();
		int initialPlayerHealth = player->getHealth();
		float playerColliderSize = player->getColliderSize();
		Vector2 enemyInitialPosition = Vector2(10 * playerColliderSize, 0);
		EnemyShip *enemy = new EnemyShip(enemyInitialPosition);
		enemy->updateSprite();
		int initialEnemyHealth = enemy->getHealth();

		//check collision, if there are - onCollision will be called
		Scene::detectCollision(enemy);
		Scene::detectCollision(player);
		player->update();
		enemy->update();
		//expect no collision
		Assert::AreEqual(initialPlayerHealth, player->getHealth());
		Assert::AreEqual(initialEnemyHealth, enemy->getHealth());

		//move to collision distance
		enemy->move(Vector2(-9.5 * playerColliderSize, 0));

		Scene::detectCollision(enemy);
		Scene::detectCollision(player);
		player->update();
		enemy->update();

		//expect health decrease because of collision
		Assert::AreEqual(initialPlayerHealth - 1, player->getHealth());
		Assert::AreEqual(initialEnemyHealth - 1, enemy->getHealth());
	}
	TEST_METHOD(Health)
	{
		// decreaseHealth method
		Spaceship *ship = new Spaceship();
		int initialHealth = ship->getHealth();
		ship->decreaseHealth();
		Assert::AreEqual(initialHealth - 1, ship->getHealth());

		// check destroy on zero health
		Spaceship *ship1 = new Spaceship();
		ship1->setHealthToZero();
		Assert::AreEqual(0, ship1->getHealth());
		ship1->update();
		Assert::AreEqual(ship1->checkIsDestroyed(), true);
	}
	TEST_METHOD(Sprites)
	{
		Drawable::loadSprites();
		//check collider size
		Spaceship *ship = new Spaceship();
		float colliderSize = ship->getColliderSize();
		Assert::IsTrue(colliderSize > 0);
		
		//updateSprite method
		sf::Vector2f initialSpritePosition = ship->getSprite()->getPosition();
		Vector2 shift = Vector2(950, 44);
		ship->move(shift);
		ship->updateSprite();
		Assert::AreEqual(initialSpritePosition + (sf::Vector2f) shift,
			ship->getSprite()->getPosition());
	}
	TEST_METHOD_CLEANUP(DestroyScene)
	{
		Scene::onDestroy();
	}
};

//#include "Cpp"
//#include "Scene.h"
//#include "SceneConstructor.h"
//#include "Body.h"
//#include "Spaceship.h"
//#include "MiniPlanet.h"
//
//TEST(PhysicsTest, SpaceshipPhysics)
//{
//	Scene *stage = new Scene();
//	stage->setIsStage(true);
//	Scene::setActiveScene(stage->getID());
//
//	Vector2 screenCenter = Vector2(Scene::SCREEN_WIDTH / 2.0f, Scene::SCREEN_HEIGHT / 2.0f);
//
//	StagePlanet* earth = new StagePlanet(screenCenter);
//
//	Spaceship* ship = new Spaceship(earth, earth->getSurfaceRadius() + 100);
//	ship->setVelocity(Vector2(0, 0));
//	Scene::processPhysics();
//	EXPECT_EQ(Vector2(0, 0), ship->getVelocity());
//	EXPECT_EQ(Vector2(earth->getSurfaceRadius() + 100, 0), ship->position);
//	ship->addForce(Vector2(1, 0));
//	Scene::processPhysics();
//	EXPECT_EQ(Vector2(1, 0), ship->getVelocity());
//	EXPECT_EQ(Vector2(earth->getSurfaceRadius() + 101, 0), ship->position);
//}
//
////int main(int argc, char *argv[])
////{
////	testing::InitGoogleTest(&argc, argv);
////	return RUN_ALL_TESTS();
////}