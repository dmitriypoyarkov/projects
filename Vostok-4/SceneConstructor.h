#pragma once
#include "Scene.h"

class SceneConstructor
{
public:
	static Scene *constructStage(int seed);
	static Scene *constructStarSystem(int seed);
};

