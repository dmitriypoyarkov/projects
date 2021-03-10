#include "pch.h"
#include "CppUnitTest.h"

#include "../Vostok-4/Vector2.h"
#include "../Vostok-4/SceneConstructor.h"
#include "../Vostok-4/Spaceship.h"
#include "MiniPlanet.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<> static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Vector2>(const Vector2& V)
{
	std::wstring str = L"(" + std::to_wstring(V.x) + L", " + std::to_wstring(V.y) + L")";
	return str;
}
TEST_CLASS(Physics)
{
public:
		
	TEST_METHOD(Ship)
	{
		Scene *stage = new Scene();
		stage->setIsStage(true);
		Scene::setActiveScene(stage->getID());
		Vector2 screenCenter = Vector2(Scene::SCREEN_WIDTH / 2.0f, Scene::SCREEN_HEIGHT / 2.0f);
		StagePlanet* earth = new StagePlanet(screenCenter);
		
		float orbit = earth->getSurfaceRadius() + 200;
		Spaceship* ship = new Spaceship(earth, orbit);

		// check coordinates
		Vector2 expectedCoords = earth->position - Vector2(0, orbit);
		Assert::AreEqual(expectedCoords, ship->position);
		
		// check velocity setter
		Vector2 newVelocity = Vector2(0, 0);
		ship->setVelocity(newVelocity);
		Assert::AreEqual(newVelocity, ship->getVelocity());

		// check gravitation
		Scene::processPhysics();
		float expectedGravityForce = earth->getMass() * Body::gravityConst / pow(orbit, 2);
		Assert::AreEqual(expectedGravityForce, ship->getVelocity().y);

		//check movement
		float expectedY = earth->position.y - orbit + expectedGravityForce;
		Assert::AreEqual(expectedY, ship->position.y);

		//check addForce
		Vector2 horizontalForce = Vector2(1, 0);
		ship->addForce(horizontalForce); // horizontal
		Scene::processPhysics();
		Assert::AreEqual(horizontalForce.x, ship->getVelocity().x);
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