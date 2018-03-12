#pragma once
#include "Actor.h"
class Actor;
class Scene
{
public:
	Scene();
	~Scene();

	void tick();

	std::vector<Actor> actors;
};

