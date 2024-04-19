#ifndef INITIALIZATION_H
#define INITIALIZATION_H

class DebugSystem {
    public:
    VkInstance* vkinstance;
    VkDebugUtilsMessengerEXT debugMessenger;

    DebugSystem(
        VkInstance* instance,
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, 
        VkDebugUtilsMessengerEXT* pDebugMessenger
    );

    ~DebugSystem();

    VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    ) {
        std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

    private:
    const std::vector<const char*> validationLayers;
};

#endif // INITIALIZATION_H