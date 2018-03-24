#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include "Model.h"

class Model;

class Actor
{
public:
	Actor(Model *model) : model(model){
		ticks = true;
		pos = glm::vec3(0.0f);
		rot = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
	}
	~Actor();
	virtual void tick(float time);
	bool doesTick();

	Model *model;

	//used for translations
	glm::mat4 matrix;
	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 rot;
	glm::vec3 scale;

private:
	bool ticks;
};

