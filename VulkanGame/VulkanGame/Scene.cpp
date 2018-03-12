#include "Scene.h"



Scene::Scene()
{
	
}


Scene::~Scene()
{
}

void Scene::tick()
{
	static auto startTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	for (unsigned int i = 0; i < actors.size(); i++) {
		if (actors.at(i).doesTick())actors.at(i).tick(time);
	}
}
