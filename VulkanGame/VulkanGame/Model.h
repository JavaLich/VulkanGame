#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include "Renderer.h"
#include "Material.h"

class Renderer;
struct Vertex;
class Model
{
public:
	Model(VkDeviceSize index, const std::string modelPath, Material *mat);
	~Model();

	Material *material;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	VkDeviceSize vertexOffset;
	VkDeviceSize vertexSizeBytes;
	VkDeviceSize indexOffset;
	VkDeviceSize indexSizeBytes;
	VkDeviceSize uniformOffset;
	VkDeviceSize modelSizeBytes;
	VkDeviceSize index;
	VkDeviceSize range;

private: 
	void loadModel(const std::string modelPath);
};

