#include "Camera.h"



Camera::Camera()
{
	pos = glm::vec3(2.0f, 2.0f, 2.0f);
	up = glm::vec3(0, 1.0f, 0);
	right = glm::vec3(0, 0, 0);
	direction = glm::vec3(0, 0, 0);
}


Camera::~Camera()
{
}

void Camera::tick(GLFWwindow* window, float time)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);
	horizontalAngle += mouseSpeed*time*float(width / 2 - xpos);
	verticalAngle += mouseSpeed*time*float(height / 2 - ypos);
	if (verticalAngle > 1.57f)verticalAngle = 1.57f;
	else if (verticalAngle < -1.57f)verticalAngle = -1.57f;
	direction = glm::vec3(cos(verticalAngle)*sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle)*cos(horizontalAngle));
	right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));
	up = glm::cross(right, direction);

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		pos = glm::vec3(2.0f, 2.0f, 2.0f);
		up = glm::vec3(0, 1.0f, 0);
		right = glm::vec3(0, 0, 0);
		direction = glm::vec3(0, 0, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		pos.y += cameraSpeed * time;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		pos += right * time * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		pos -= right * time * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		pos += direction * time * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		pos -= direction * time * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		pos.y -= cameraSpeed * time;
	}
	view = glm::lookAt(pos, pos + direction, up);
	proj = glm::perspective(glm::radians(initialFOV), width / (float)height, 0.01f, 1000.0f);
	proj[1][1] *= -1;
}
