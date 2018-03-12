#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include <tiny_obj_loader.h>

#include <stb_image.h>

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
#include <unordered_map>


#include "Application.h"
#include "Model.h"
#include "Helper.h"
#include "Scene.h"
#include "Actor.h"


#include "vk_mem_alloc.h"


#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif


const int WIDTH = 800;
const int HEIGHT = 600;

const std::string MODEL_PATH = "assets/models/chalet.obj";
const std::string TEXTURE_PATH = "assets/models/chalet.jpg";
const std::string MODEL_PATH1 = "assets/models/stall.obj";

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


struct Vertex {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);
		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

		return attributeDescriptions;
	}

	bool operator==(const Vertex& other)const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}

};


namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^
				(hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
				(hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}

struct UniformBufferObject {
	glm::mat4 mvp;
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
class ModelManager;
class Scene;
class Renderer
{
public:
	Renderer();
	~Renderer();
	void drawFrame();
	void recreateSwapChain();
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer, VmaAllocation& bufferMemory, VmaMemoryUsage memoryUsage, VmaAllocationInfo& allocInfo);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void loop();

	void updateUniformBuffer();

	GLFWwindow* window;
	VkInstance instance;
	VmaAllocator allocator;
	static VkDeviceSize minUniformBufferOffsetAlignment;
	ModelManager *modelManager;
	Scene* scene;

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


	VkDescriptorPool descriptorPool;
	VkDescriptorSet descriptorSet;
	VkImage textureImage;
	VmaAllocation textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;
	VkImage depthImage;
	VmaAllocation depthImageMemory;
	VkImageView depthImageView;
	VkDeviceSize fullBufferSize;


	void initVulkan();
	void loadModel();
	void createDepthResources();
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat();
	bool hasStencilComponent(VkFormat format);
	void createTextureSampler();
	void createTextureImageView();
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	void createDescriptorSet();
	void createDescriptorPool();
	void createAllocator();
	void cleanup();
	void createGraphicsPipeline();
	void cleanupSwapChain();
	void createSemaphores();
	void createCommandBuffers();
	void allocateCommandBuffers();
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
	
	static void onWindowResized(GLFWwindow* window, int width, int height);
	void createTextureImage();
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VmaMemoryUsage memoryUsage, VkImage& image, VmaAllocation& imageMemory, VmaAllocationInfo& allocInfo);
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newImageLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

};
