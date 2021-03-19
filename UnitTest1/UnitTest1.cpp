#include "pch.h"
#include "CppUnitTest.h"

#include "../Vostok-4/Vector2.h"
#include "../Vostok-4/SceneConstructor.h"
#include "../Vostok-4/EnemyShip.h"
#include "../Vostok-4/PlayerShip.h"
#include "../Vostok-4/MiniPlanet.h"
#include "../Vostok-4/Bullet.h"

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

static const float floatError = 0.00001f;

TEST_MODULE_INITIALIZE(LoadSprites)
{
	Drawable::loadSprites();
}

/* Abstract class Body - testing on child classes */
TEST_CLASS(BodyTest)
{
public:
	TEST_METHOD_CLEANUP(DestroyScene)
	{
		Scene::onDestroy();
	};

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
	};

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
	};

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
	};

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
	};
	
	TEST_METHOD(Collisions)
	{
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
	};
	
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
	};
	
	TEST_METHOD(Sprites)
	{
		//check collider size
		MiniPlanet *planet = new MiniPlanet();
		float colliderSize = planet->getColliderSize();
		Assert::IsTrue(colliderSize > 0, L"Collider 0");
		
		//updateSprite method
		sf::Vector2f initialSpritePosition = planet->getSprite()->getPosition();
		Vector2 shift = Vector2(950, 44);
		planet->move(shift);
		planet->updateSprite();
		Assert::AreEqual(initialSpritePosition + (sf::Vector2f) shift,
			planet->getSprite()->getPosition());
	};

};

/*abstract class Planet and derived classes Star and MiniPlanet*/
TEST_CLASS(PlanetTest1)
{
	Star *star;
	MiniPlanet *planet;
	float orbit;
	float angle;
	float speed;

	TEST_METHOD_INITIALIZE(StarAndPlanet)
	{
		star = new Star(); // standart Body constructor
		orbit = star->getColliderSize() + 400;
		angle = 0.5 * 3.14;
		speed = 2;
		planet = new MiniPlanet(star, orbit, speed, angle);
	};

	TEST_METHOD_CLEANUP(DestroyScene)
	{
		Scene::onDestroy();
	};

	TEST_METHOD(Constructorss)
	{
		Vector2 expectedPosition = star->getPosition() + Vector2(orbit * cos(angle), orbit * sin(angle));
		Assert::AreEqual(expectedPosition, star->getPosition() + planet->getPosition());
		float error = speed - (planet->getVelocity()).magnitude();
		Assert::IsTrue(error < floatError * speed, L"Speed is not as expected");
	};

	TEST_METHOD(Orbitingss)
	{
		// check if planet goes along orbit
		Vector2 initialPosition = planet->getPosition();
		float initialDistance = (planet->getPosition() - star->getPosition()).magnitude();
		planet->update();
		planet->travel();
		float delta = (planet->getPosition() - initialPosition).magnitude();
		Assert::IsTrue(speed - delta < floatError * speed, L"Speed is not as expected"); // moved with adjusted speed
		Assert::IsTrue(planet->getPosition().x > initialPosition.x); // moved to the right
		float newDistance = (planet->getPosition() - star->getPosition()).magnitude();
		Assert::IsTrue(newDistance - initialDistance < floatError * newDistance, L"Distance changed"); // orbit is the same (may be not equal - float error)
		
		// many updates
		int updateCount = 500 + rand() % 300; 
		for (int i = 0; i < updateCount; i++)
		{
			planet->update();
			planet->travel();
		}

		float finalDistance = (planet->getPosition() - star->getPosition()).magnitude();
		//distanceDifference = finalDistance - initialDistance;
		Assert::IsTrue(initialDistance - finalDistance < floatError * finalDistance);
		//Assert::IsTrue(distanceDifference < 0.01f); // still on the same orbit
	};

	TEST_METHOD(PlanetCollisionss)
	{
		//planets and stars are not affected by collisions.
		MiniPlanet *planet1 = new MiniPlanet(planet->getPosition());
		int planetInitialHealth = planet->getHealth();
		int planet1InitialHealth = planet1->getHealth();
		Scene::detectCollision(planet);
		Scene::detectCollision(planet1);
		planet->update();
		planet1->update();
		Assert::AreEqual(planet->getHealth(), planetInitialHealth);
		Assert::AreEqual(planet1->getHealth(), planet1InitialHealth); 

		Star *star1 = new Star(star->getPosition());
		int starInitialHealth = star->getHealth();
		int star1InitialHealth = star1->getHealth();
		Scene::detectCollision(star);
		Scene::detectCollision(star1);
		star->update();
		star1->update();
		Assert::AreEqual(star->getHealth(), starInitialHealth);
		Assert::AreEqual(star1->getHealth(), star1InitialHealth);
	};

	TEST_METHOD(StarManagement)
	{
		Assert::IsTrue(Scene::getActiveStar() == star, L"Star is not ActiveStar");
		Star *newStar = new Star(Vector2(100000000000, 0)); //far enough from the old one
		PlayerShip *player = new PlayerShip(star->getPosition() + Vector2(0, 2 * newStar->getSurfaceRadius()));
		Assert::IsTrue(Scene::getPlayer() == player);
		star->update();
		newStar->update();
		Assert::IsTrue(Scene::getActiveStar() == star, L"Star is not ActiveStar anymore");
		player->move(newStar->getPosition() - star->getPosition()); //move player to the new star orbit
		star->update();
		newStar->update();
		Assert::IsTrue(Scene::getActiveStar() == newStar, L"New star hasn't activated"); //expect to activate new star
	}
};