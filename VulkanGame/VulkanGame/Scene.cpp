#include "Scene.h"



Scene::Scene()
{
	
}


Scene::~Scene()
{
}

void Scene::tick(float time)
{
	
	for (unsigned int i = 0; i < actors.size(); i++) {
		if (actors.at(i).doesTick())actors.at(i).tick(time);
	}
}

void Scene::addActor(Actor actor, uint16_t count)
{
	for (int i = 0; i < count; i++) {
		actors.push_back(actor);
	}
}
