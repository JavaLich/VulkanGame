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
