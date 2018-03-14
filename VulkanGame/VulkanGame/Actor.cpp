#include "Actor.h"





Actor::~Actor()
{
}

void Actor::tick(float time)
{
	matrix = glm::rotate(matrix, time * glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

bool Actor::doesTick()
{
	return ticks;
}
