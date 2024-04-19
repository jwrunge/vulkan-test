#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "./init/debug.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
const char* APP_NAME = "Hello Triangle";

class HelloTriangleApplication {
public:
    HelloTriangleApplication() {
        initWindow();
        initVulkan();
    }

    ~HelloTriangleApplication() {
        cleanup();
    }

    void run() {
        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

private:
    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    DebugSystem* debugSystem;

    void initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);     // disable resizable windows for now

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan() {
        createInstance();
        // setupDebugMessenger();
        pickPhysicalDevice();
    }

    void createInstance() {
        if(enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("Validation layers requested but not available!");
        }

        VkApplicationInfo appInfo{
            .sType =                VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName =     APP_NAME,
            .applicationVersion =   VK_MAKE_VERSION(1, 0, 0),
            .pEngineName =          "No Engine",
            .engineVersion =        VK_MAKE_VERSION(1, 0, 0),
            .apiVersion =           VK_API_VERSION_1_0,
        };

        VkInstanceCreateInfo createInfo{
            .sType =                    VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo =         &appInfo,
        };

        // Extensions
        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        // VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        // if(enableValidationLayers) {
        //     createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        //     createInfo.ppEnabledLayerNames = validationLayers.data();

        //     populateDebugMessengerCreateInfo(debugCreateInfo);
        //     createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        // } else {
        //     createInfo.enabledLayerCount = 0;
        //     createInfo.pNext = nullptr;
        // }

        // Create instance
        auto instance = vkCreateInstance(&createInfo, nullptr, &instance);
        if(instance != VK_SUCCESS) {
            throw std::runtime_error("Failed to create instance!");
        }
        // else {
        //     debugSystem = new DebugSystem(&instance, &debugCreateInfo, nullptr, &debugSystem->debugMessenger);
        // }
    }

    void pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if(deviceCount == 0) {
            throw std::runtime_error("Failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for(const auto& device : devices) {
            if(isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if(physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("Failed to find a suitable GPU!");
        }
    }

    bool isDeviceSuitable(VkPhysicalDevice device) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
               deviceFeatures.geometryShader;
    }

    std::vector<const char*> getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        // if(enableValidationLayers) {
        //     extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        // }

        return extensions;
    }

    bool checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for(const char* layerName : validationLayers) {
            bool layerFound = false;

            for(const auto& layerProperties : availableLayers) {
                if(strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if(!layerFound) {
                return false;
            }
        }

        return true;
    }

    void cleanup() {
        delete debugSystem;
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}