#include "UI.h"
#include "Scene.h"

const int UI::aimDistance = 5;

void UI::draw()
{
	drawAim();
}

void UI::drawAim()
{
	Vector2 playerPosition = Scene::getPlayer()->position;
	Vector2 playerDirection = Scene::getPlayer()->getMovingDirection();
	float aimScale = 0.002f*Scene::window->getView().getSize().x;
	Vector2 aimPosition = playerPosition + playerDirection * aimDistance * aimScale;
	
	
	sf::CircleShape point;
	point.setPosition(aimPosition);
	point.setRadius(aimScale);
	point.setPointCount(3);
	point.setOrigin(aimScale / 2, aimScale / 2);
	Scene::window->draw(point);
}

