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
	}
	~Actor();
	virtual void tick(float time);
	bool doesTick();

	Model *model;

	//used for translations
	glm::mat4 matrix;

private:
	bool ticks;
};

