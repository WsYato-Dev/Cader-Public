#include "Instance.h"

#include "Cader/Types/Common.h"
#include "Cader/Window/Window.h"
#include "Utility.h"

#include <assert.h>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>

namespace CDR::VK {

	Instance::Instance(const Window& pWindow)
	{
		InitInstance();
		InitSurface(pWindow);
	}

	Instance::~Instance()
	{
		vkDestroySurfaceKHR(mInstance, mSurface, nullptr);
		vkDestroyInstance(mInstance, nullptr);
	}

	void Instance::InitInstance()
	{
		VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
		appInfo.apiVersion = VK_API_VERSION_1_3;
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pApplicationName = "Cader Application";
		appInfo.pEngineName = "Cader";

		u32 extensionsCount = 0;
		const Text* extensions = glfwGetRequiredInstanceExtensions(&extensionsCount);

		VkInstanceCreateInfo instanceInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
		instanceInfo.pApplicationInfo = &appInfo;
		instanceInfo.enabledExtensionCount = extensionsCount;
		instanceInfo.ppEnabledExtensionNames = extensions;

	#if defined(CDR_DEBUG)

		constexpr u8 requestedLayersCount = 1;
		constexpr Text requestedLayers[requestedLayersCount]
		{
			"VK_LAYER_KHRONOS_validation"
		};

		u32 layersCount;
		VK_VERIFY(vkEnumerateInstanceLayerProperties(&layersCount, nullptr));
		assert(layersCount);

		std::vector<VkLayerProperties> layers(layersCount);
		VK_VERIFY(vkEnumerateInstanceLayerProperties(&layersCount, &layers[0]));

		u8 layersFound = 0;

		for(u8 i = 0; i < (u8)requestedLayersCount; i++)
		{
			for(const auto& layer : layers)
			{
				if(strcmp(requestedLayers[i], layer.layerName) == 0)
				{
					layersFound++;
					break;
				}
			}
		}

		assert(layersFound == requestedLayersCount);

		instanceInfo.enabledLayerCount = requestedLayersCount;
		instanceInfo.ppEnabledLayerNames = &requestedLayers[0];

	#else

		instanceInfo.enabledLayerCount = 0;
		instanceInfo.ppEnabledLayerNames = nullptr;

	#endif

		VK_VERIFY(vkCreateInstance(&instanceInfo, nullptr, &mInstance));
	}

	void Instance::InitSurface(const Window& pWindow)
	{
		GLFWwindow* window = pWindow.GetNativeWindow();
		VK_VERIFY(glfwCreateWindowSurface(mInstance, window, nullptr, &mSurface));
	}

}