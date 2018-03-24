#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include <iostream>

class Camera
{
public:
	Camera();
	~Camera();
	void tick(GLFWwindow *window, float time);
	glm::vec3 pos;
	glm::vec3 direction;
	glm::vec3 up;
	glm::vec3 right;
	glm::mat4 view;
	glm::mat4 proj;
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float initialFOV = 45.0f;
	float cameraSpeed = 3.0f;
	float mouseSpeed = 0.05f;
	
};

