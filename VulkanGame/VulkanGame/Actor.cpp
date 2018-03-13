#include "Actor.h"





Actor::~Actor()
{
}

void Actor::tick(float time)
{
	matrix = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

bool Actor::doesTick()
{
	return ticks;
}
