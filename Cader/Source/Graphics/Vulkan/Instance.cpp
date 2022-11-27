#include "Instance.h"

#include "Cader/Types/Common.h"
#include "Cader/Utility/Assert.h"
#include "Cader/Window/Window.h"

#include "Utility.h"

#include <array>
#include <string>
#include <vector>

#define GLFW_INCLUDE_NONE
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
		appInfo.pEngineName = "Cader Engine";

		u32 extensionsCount;
		const Text* extensions = glfwGetRequiredInstanceExtensions(&extensionsCount);

		VkInstanceCreateInfo instanceInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
		instanceInfo.pApplicationInfo = &appInfo;
		instanceInfo.enabledExtensionCount = extensionsCount;
		instanceInfo.ppEnabledExtensionNames = extensions;

	#if !defined(CDR_FINAL)

		constexpr std::array<Text, 1> requestedLayers
		{
			"VK_LAYER_KHRONOS_validation"
		};

		u32 layersCount;
		VK_VERIFY(vkEnumerateInstanceLayerProperties(&layersCount, nullptr));
		CDR_ASSERT(layersCount);

		std::vector<VkLayerProperties> layers(layersCount);
		VK_VERIFY(vkEnumerateInstanceLayerProperties(&layersCount, &layers[0]));

		u8 layersFound = 0;

		for(u8 i = 0; i < (u8)requestedLayers.size(); i++)
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

		CDR_ASSERT(layersFound == requestedLayers.size());

		instanceInfo.enabledLayerCount = (u32)requestedLayers.size();
		instanceInfo.ppEnabledLayerNames = &requestedLayers[0];

	#else // !defined(CDR_FINAL)

		instanceInfo.enabledLayerCount = 0;

	#endif // !defined(CDR_FINAL)

		VK_VERIFY(vkCreateInstance(&instanceInfo, nullptr, &mInstance));
	}

	void Instance::InitSurface(const Window& pWindow)
	{
		GLFWwindow* window = pWindow.GetNativeWindow();
		VK_VERIFY(glfwCreateWindowSurface(mInstance, window, nullptr, &mSurface));
	}

}