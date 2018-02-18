#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>

#include "Application.h"

const int WIDTH = 800;
const int HEIGHT = 600;
//const char* TITLE = "Vulkan";


const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
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
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;

	void initVulkan();
	void cleanup();
	void createGraphicsPipeline();
	void cleanupSwapChain();
	void createSemaphores();
	void createCommandBuffers();
	void createCommandPool();
	void createFramebuffers();
	void createRenderPass();
	void createInstance();
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice physicalDevice);
	bool checkValidationLayerSupport();
	void checkRequiredExtensionsPresent(std::vector<VkExtensionProperties> availableExt, const char** requiredExt, int requiredExtCount);
	static std::vector<char> readFile(const std::string& filename);
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
	
};

