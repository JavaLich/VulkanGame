#pragma once
#include "Actor.h"
class Actor;
class Scene
{
public:
	Scene();
	~Scene();

	void tick(float time);

	std::vector<Actor> actors;
};

