#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#include <vk_mem_alloc.h>
#include <iostream>

class Material
{
public:
	Material(VkImage image, VkImageView imageView) : image(image), imageView(imageView) {
		destroyed = false;
	}
	~Material();
	void destroy(VmaAllocator *allocator, VkDevice *device);
	VmaAllocation imageMemory;
	VkImage image;
	VkImageView imageView;
	bool destroyed;
};

