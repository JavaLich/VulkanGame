#include "Actor.h"





Actor::~Actor()
{
}

void Actor::tick(float time)
{
	for (unsigned int i = 0; i < model->instanceData.size(); i++) {
		matrix = glm::mat4(1.0f);

		pos.x = 5 * i;

		matrix = glm::rotate(matrix, rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
		matrix = glm::translate(matrix, pos);
		matrix = glm::scale(matrix, scale);
		model->instanceData[i] = { {matrix} };
	}
}

bool Actor::doesTick()
{
	return ticks;
}
