#include "Application.h"
#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"
Application::Application()
{
	renderer = new Renderer();
}

void Application::run() {
	setupDebugCallback();
	mainLoop();
	cleanup();
}

void Application::mainLoop() {
	double previousTime = glfwGetTime();
	int frameCount = 0;
	while (!glfwWindowShouldClose(renderer->window)) {
		renderer->loop();
		glfwPollEvents();
		double currentTime = glfwGetTime();
		frameCount++;
		if (currentTime - previousTime >= 1.0) {
			std::cout << "FPS: " << frameCount << std::endl;
			frameCount = 0;
			previousTime += 1.0;
		}
	}
}

void Application::setupDebugCallback() {
	if (!enableValidationLayers) return;
	VkDebugReportCallbackCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	createInfo.pfnCallback = debugCallback;
	if (CreateDebugReportCallbackEXT(renderer->instance, &createInfo, nullptr, &callback) != VK_SUCCESS) {
		throw std::runtime_error("Failed to setup debug callback");
	}
}

void Application::DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr) {
		func(instance, callback, pAllocator);
	}
}

VkResult Application::CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}



VKAPI_ATTR VkBool32 VKAPI_CALL Application::debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
	std::cerr << "Validation layer: " << msg << std::endl;

	return VK_FALSE;
}

void Application::cleanup() {
	DestroyDebugReportCallbackEXT(renderer->instance, callback, nullptr);
	glfwDestroyWindow(renderer->window);
}

Application::~Application()
{
}
