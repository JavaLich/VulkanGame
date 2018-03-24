#pragma once
#include "Actor.h"
class Actor;
class Scene
{
public:
	Scene();
	~Scene();

	void tick(float time);
	void addActor(Actor actor, uint16_t count);

	std::vector<Actor> actors;
};

