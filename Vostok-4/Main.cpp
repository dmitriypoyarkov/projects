#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <Windows.h>

#include "Drawable.h"
#include "Scene.h"
#include "SceneConstructor.h"
#include "Body.h"
#include "Bullet.h"

namespace py = pybind11;

PYBIND11_MODULE(vostok4, m) {

	m.doc() = "Vostok-4 library for Python";

    py::class_<Vector2>(m, "Vector2")
        .def(py::init<float, float>())
        .def_readwrite("x", &Vector2::x)
        .def_readwrite("y", &Vector2::y);
    py::class_<Drawable>(m, "Drawable")
        .def("get_sprite_name", &Drawable::getSpriteName)
        .def("get_collider_size", &Drawable::getColliderSize)
        .def("set_collider_size", &Drawable::setColliderSize);
    py::class_<Body, Drawable>(m, "Body")
        .def("get_position", &Body::getPosition)
        .def("get_rotation", &Body::getRotation)
        .def("check_is_destroyed", &Body::checkIsDestroyed)
        .def("get_sceneID", &Body::getSceneID);
        
    py::class_<Bullet, Body>(m, "Bullet")
        .def(py::init<Vector2, float, Vector2, Body*>());

    py::class_<Scene>(m, "Scene")
        .def("process_physics", &Scene::processPhysics, R"pbdoc(
            Make one iteration of physics.
            )pbdoc")
        .def("manage_scene", &Scene::manageScene)
        .def("get_active_camera", &Scene::getActiveCamera)
        .def("reset_body_index", &Scene::resetBodyIndex)
        .def("get_cur_body", &Scene::getCurBody)
        .def("get_next_body", &Scene::getNextBody);

    m.def("init_game", &SceneConstructor::initiateGameWithStarSystem, R"pbdoc(
        Create initial star system to start the game.
        )pbdoc");

}
//PYBIND11_MODULE(vostok4, m) {
//	m.def("fast_tanh2", &tanh_impl, R"pbdoc(
//        Compute a hyperbolic tangent of a single argument expressed in radians.
//    )pbdoc");
//
//#ifdef VERSION_INFO
//	m.attr("__version__") = VERSION_INFO;
//#else
//	m.attr("__version__") = "dev";
//#endif
//}

//#include <vld.h>
//#include <string>
//#include <iostream>
//#include "SceneConstructor.h"
//#include "Scene.h"
//
//void showStartMessage()
//{
//	std::cout << "\tVOSTOK-4" << std::endl
//		<< "Press Shift to accelerate, A/D - rotate" << std::endl
//		<< "Camera control: \"+\" and \"-\"" << std::endl
//		<< "Ship control: Accelerate: LShift" << std::endl
//		<< "Destroy everyone in this star system!" << std::endl
//		<< "Use Space to shoot." << std::endl
//		<< "Enable\\disable orbit drawing: O" << std::endl
//		<< "Switch between engines with R, T, Y." << std::endl;
//}
//void runGame()
//{
//	Scene::window = new sf::RenderWindow(sf::VideoMode(Scene::SCREEN_WIDTH, Scene::SCREEN_HEIGHT), "Space!");
//	Scene::window->setFramerateLimit(60);
//	Drawable::loadSprites();
//	srand(0);
//	showStartMessage();
//	SceneConstructor::initiateGameWithStarSystem(rand());
//	
//	sf::Event event;
//	while (Scene::window->isOpen())
//	{
//		while (Scene::window->pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				Scene::window->close();
//				Scene::onDestroy();
//			}
//			else if (event.type == sf::Event::Resized)
//				Scene::window->setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
//		}
//		Scene::processPhysics();
//		Scene::processGraphics();
//		Scene::manageScene();
//	}
//	delete Scene::window;
//}
//
//int main()
//{
//	runGame();
//	return 0;
//}
