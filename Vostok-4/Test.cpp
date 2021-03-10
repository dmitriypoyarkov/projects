#include "Cpp"
#include "Scene.h"
#include "SceneConstructor.h"
#include "Body.h"
#include "Spaceship.h"
#include "MiniPlanet.h"

TEST(PhysicsTest, SpaceshipPhysics)
{
	Scene *stage = new Scene();
	stage->setIsStage(true);
	Scene::setActiveScene(stage->getID());

	Vector2 screenCenter = Vector2(Scene::SCREEN_WIDTH / 2.0f, Scene::SCREEN_HEIGHT / 2.0f);

	StagePlanet* earth = new StagePlanet(screenCenter);

	Spaceship* ship = new Spaceship(earth, earth->getSurfaceRadius() + 100);
	ship->setVelocity(Vector2(0, 0));
	Scene::processPhysics();
	EXPECT_EQ(Vector2(0, 0), ship->getVelocity());
	EXPECT_EQ(Vector2(earth->getSurfaceRadius() + 100, 0), ship->position);
	ship->addForce(Vector2(1, 0));
	Scene::processPhysics();
	EXPECT_EQ(Vector2(1, 0), ship->getVelocity());
	EXPECT_EQ(Vector2(earth->getSurfaceRadius() + 101, 0), ship->position);
}

//int main(int argc, char *argv[])
//{
//	testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}