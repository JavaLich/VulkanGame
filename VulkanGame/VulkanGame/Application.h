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
#include "Renderer.h"
class Renderer;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class Application {
public:
	void run();
	Application();
	~Application();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
	static void onWindowResized(GLFWwindow* window, int width, int height);
	void setupDebugCallback();
	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);

private:
	VkDebugReportCallbackEXT callback;
	void cleanup();
	void mainLoop();
	Renderer* renderer;
};