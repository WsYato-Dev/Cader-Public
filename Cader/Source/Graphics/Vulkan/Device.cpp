#include "Device.h"

#include "Instance.h"
#include "Utility.h"

#include <assert.h>
#include <string>
#include <vector>

namespace CDR::VK {

	constexpr u8 RequiredExtensionsCount = 1;
	constexpr Text RequiredExtensions[RequiredExtensionsCount]
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	bool QueueIndicies::IsComplete() const noexcept
	{
		return graphicsIndex >= 0 && presentIndex >= 0 && transferIndex >= 0;
	}

	u8 QueueIndicies::GetUniqueIndicies(i8 pIndicies[3]) const
	{
		u8 count = 0;

		pIndicies[count++] = graphicsIndex;

		if(presentIndex != graphicsIndex)
			pIndicies[count++] = presentIndex;

		if(transferIndex != graphicsIndex)
			pIndicies[count++] = transferIndex;

		return count;
	}

	Device::Device(const Instance& pInstance)
		: mInstance(pInstance)
	{
		InitPhysicalDevice();
		InitDevice();
	}

	Device::~Device()
	{
		vkDestroyDevice(mDevice, nullptr);
	}

	void Device::InitPhysicalDevice()
	{
		u32 physicalDevicesCount;
		VK_VERIFY(vkEnumeratePhysicalDevices(mInstance.GetInstance(), &physicalDevicesCount, nullptr));
		assert(physicalDevicesCount);

		std::vector<VkPhysicalDevice> physicalDevices(physicalDevicesCount);
		VK_VERIFY(vkEnumeratePhysicalDevices(mInstance.GetInstance(), &physicalDevicesCount, &physicalDevices[0]));

		struct PhysicalDeviceRating final
		{
			u8 index = 0;
			u8 score = 0;
			QueueIndicies queueIndicies = {};
		};

		PhysicalDeviceRating physicalDeviceRating;

		for(u8 i = 0; i < (u8)physicalDevicesCount; i++)
		{
			QueueIndicies queueIndicies;
			const u8 score = RatePhysicalDevice(physicalDevices[i], queueIndicies);

			if(score > physicalDeviceRating.score)
			{
				physicalDeviceRating.index = i;
				physicalDeviceRating.score = score;
				physicalDeviceRating.queueIndicies = queueIndicies;
			}
		}

		assert(physicalDeviceRating.score);

		mPhysicalDevice = physicalDevices[physicalDeviceRating.index];
		mQueueIndicies = physicalDeviceRating.queueIndicies;
	}

	u8 Device::RatePhysicalDevice(const VkPhysicalDevice& pPhysicalDevice, QueueIndicies& pQueueIndicies) const
	{
		u32 score = 0;

		u32 extensionsCount;
		VK_VERIFY(vkEnumerateDeviceExtensionProperties(pPhysicalDevice, nullptr, &extensionsCount, nullptr));

		if(extensionsCount <= 0)
			return 0;

		std::vector<VkExtensionProperties> extensions(extensionsCount);
		VK_VERIFY(vkEnumerateDeviceExtensionProperties(pPhysicalDevice, nullptr, &extensionsCount, &extensions[0]));

		u8 extensionsFound = 0;

		for(u8 i = 0; i < RequiredExtensionsCount; i++)
		{
			for(const auto& extension : extensions)
			{
				if(strcmp(RequiredExtensions[i], extension.extensionName) == 0)
				{
					extensionsFound++;
					break;
				}
			}
		}

		if(extensionsFound != RequiredExtensionsCount)
			return 0;

		u32 queueFamilyPropertiesCount;
		vkGetPhysicalDeviceQueueFamilyProperties(pPhysicalDevice, &queueFamilyPropertiesCount, nullptr);

		if(queueFamilyPropertiesCount <= 0)
			return 0;

		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertiesCount);
		vkGetPhysicalDeviceQueueFamilyProperties(pPhysicalDevice, &queueFamilyPropertiesCount, &queueFamilyProperties[0]);

		for(u8 i = 0; i < (u8)queueFamilyPropertiesCount; i++)
		{
			if(pQueueIndicies.graphicsIndex < 0 && queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				pQueueIndicies.graphicsIndex = i;
				goto ASSIGNED;
			}

			if(pQueueIndicies.presentIndex < 0)
			{
				u32 surfaceSupported;
				VK_VERIFY(vkGetPhysicalDeviceSurfaceSupportKHR(pPhysicalDevice, i, mInstance.GetSurface(), &surfaceSupported));

				if(surfaceSupported)
				{
					pQueueIndicies.presentIndex = i;
					goto ASSIGNED;
				}
			}

			if(pQueueIndicies.transferIndex < 0 && queueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				pQueueIndicies.transferIndex = i;
				goto ASSIGNED;
			}

		ASSIGNED:
			if(pQueueIndicies.IsComplete())
				break;
		}

		if(pQueueIndicies.graphicsIndex < 0)
			return 0;

		if(pQueueIndicies.presentIndex < 0)
			pQueueIndicies.presentIndex = pQueueIndicies.graphicsIndex;
		else
			score++;

		if(pQueueIndicies.transferIndex < 0)
			pQueueIndicies.transferIndex = pQueueIndicies.graphicsIndex;
		else
			score++;

		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(pPhysicalDevice, &properties);

		switch(properties.deviceType)
		{
			case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: score += 100; break;
			case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: score += 50; break;
			case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: score += 20; break;
			case VK_PHYSICAL_DEVICE_TYPE_CPU: score += 10; break;
			default: return 0;
		}

		return score;
	}

	void Device::InitDevice()
	{
		VkDeviceCreateInfo deviceInfo = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
		deviceInfo.enabledExtensionCount = RequiredExtensionsCount;
		deviceInfo.ppEnabledExtensionNames = RequiredExtensions;

		i8 uniqueQueues[3];
		u8 uniqueQueuesCount = mQueueIndicies.GetUniqueIndicies(uniqueQueues);

		VkDeviceQueueCreateInfo queueCreateInfos[3] = {};

		constexpr float queuePriority = 1.0f;

		for(u8 i = 0; i < uniqueQueuesCount; i++)
		{
			queueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfos[i].pQueuePriorities = &queuePriority;
			queueCreateInfos[i].queueFamilyIndex = uniqueQueues[i];
			queueCreateInfos[i].queueCount = 1;
		}

		deviceInfo.queueCreateInfoCount = uniqueQueuesCount;
		deviceInfo.pQueueCreateInfos = queueCreateInfos;

		VkPhysicalDeviceFeatures deviceFeatures = {};

		deviceInfo.pEnabledFeatures = &deviceFeatures;

		VK_VERIFY(vkCreateDevice(mPhysicalDevice, &deviceInfo, nullptr, &mDevice));

		vkGetDeviceQueue(mDevice, mQueueIndicies.graphicsIndex, 0, &mGraphicsQueue);
		vkGetDeviceQueue(mDevice, mQueueIndicies.presentIndex, 0, &mPresentQueue);
		vkGetDeviceQueue(mDevice, mQueueIndicies.transferIndex, 0, &mTransferQueue);
	}

	void Device::WaitIdle()
	{
		VK_VERIFY(vkDeviceWaitIdle(mDevice));
	}

}