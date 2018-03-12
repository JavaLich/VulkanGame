#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#include <vk_mem_alloc.h>


#include "Model.h"

class Model;
class Renderer;
class ModelManager
{
public:
	ModelManager(Renderer* rend);
	~ModelManager();
	std::vector<Model> models;
	VkBuffer buffer;
	VmaAllocation bufferMemory;
	VmaAllocationInfo allocInfo;
	VkDeviceSize bufferSize;
	void addModel(const std::string modelPath);
	void init(uint32_t numOfActors);
	void updateUniform(VkDeviceSize offset, UniformBufferObject ubo);
	void cleanup();
	static Renderer *renderer;
	VkDeviceSize firstUniformOffset;
};

