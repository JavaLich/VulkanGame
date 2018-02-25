#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <chrono>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>
#include <array>

#include "Application.h"
#include "Helper.h"

#include "vk_mem_alloc.h"

const int WIDTH = 800;
const int HEIGHT = 600;
//const char* TITLE = "Vulkan";


const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct Vertex {
	glm::vec2 pos;
	glm::vec3 color;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}

};

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

struct QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete() {
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class Renderer
{
public:
	Renderer();
	~Renderer();
	void drawFrame();
	void recreateSwapChain();
	void loop();

	void updateUniformBuffer();

	GLFWwindow* window;
	VkInstance instance;

private:
	VkDevice device;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkQueue graphicsQueue;
	VkSurfaceKHR surface;
	VkQueue presentQueue;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkExtent2D swapChainExtent;
	VkFormat swapChainImageFormat;
	std::vector<VkImageView> swapChainImageViews;
	VkRenderPass renderPass;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	std::vector<Vertex> vertices = {
		{ { -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f } },
		{ { 0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f } },
		{ { 0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f } },
		{ { -0.5f, 0.5f },{ 1.0f, 1.0f, 1.0f } }
	};
	std::vector<uint16_t> indices = {
		0, 1, 2, 2, 3, 0
	};
	VkBuffer vertexBuffer;
	VmaAllocation vertexBufferMemory;
	VmaAllocationInfo allocInfo;
	VmaAllocator allocator;
	VkDescriptorPool descriptorPool;
	VkDescriptorSet descriptorSet;
	VkDeviceSize minUniformBufferOffsetAlignment;


	void initVulkan();
	void createDescriptorSet();
	void createDescriptorPool();
	void createAllocator();
	void cleanup();
	void createGraphicsPipeline();
	void cleanupSwapChain();
	void createSemaphores();
	void createVertexBuffers();
	void createCommandBuffers();
	void createCommandPool();
	void createFramebuffers();
	void createRenderPass();
	void createInstance();
	void createDescriptorSetLayout();
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physicalDevice);
	bool checkValidationLayerSupport();
	void checkRequiredExtensionsPresent(std::vector<VkExtensionProperties> availableExt, const char** requiredExt, int requiredExtCount);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createImageViews();
	void createSwapChain();
	std::vector<const char*> getRequiredExtensions();
	void createLogicalDevice();
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	void pickPhysicalDevice();
	int rateDeviceSuitability(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void initWindow();
	void createSurface();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer, VmaAllocation& bufferMemory, VmaMemoryUsage memoryUsage, VmaAllocationInfo& allocInfo);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	static void onWindowResized(GLFWwindow* window, int width, int height);

};

