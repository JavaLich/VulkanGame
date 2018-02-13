#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "Vulkan";

class Application {
public: 
	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	VkInstance instance;
	GLFWwindow* window;

	void initWindow() {
		if (glfwInit()==GLFW_FALSE) {
			std::cout << "GLFW failed to initialize." << std::endl;
		}
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		
		window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
	}

	void createInstance() {
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Vulkan Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionsCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

		createInfo.enabledExtensionCount = glfwExtensionsCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		createInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
			throw std::runtime_error("VkInstance failed to initialize");
		}

		uint32_t extensionsCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionsCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, extensions.data());

		std::cout << "Available extensions: " << std::endl;

		for (const auto& extension : extensions) {
			std::cout << "\t" << extension.extensionName << std::endl;
		}

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
		std::cout << "GLFW extensions: " << std::endl;
		for (auto i = 0; i < glfwExtensionsCount; ++i) {
			std::cout <<  "\t" <<glfwExtensions[i] << std::endl;
		}
		checkRequiredExtensionsPresent(extensions, glfwExtensions, glfwExtensionsCount);
	}

	void checkRequiredExtensionsPresent(std::vector<VkExtensionProperties> availableExt, const char** requiredExt, int requiredExtCount) {
		for (int i = 0; i < requiredExtCount; i++) {
			bool found = false;
			for (const auto& extension : availableExt) {
				if (strcmp(requiredExt[i], extension.extensionName)) {
					found = true;
				}
			}
			if (!found) {
				throw std::runtime_error("Missing vulkan extension");
			}
		}
		std::cout << "Extension requirement fulfilled" << std::endl;
	}

	void initVulkan() {
		createInstance();
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	void cleanup() {
		vkDestroyInstance(instance, nullptr);
		glfwDestroyWindow(window);
		glfwTerminate();
	}
};

int main() {
	Application app;

	try {
		app.run();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}