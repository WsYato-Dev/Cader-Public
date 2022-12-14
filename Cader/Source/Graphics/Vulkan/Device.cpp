#include "Device.h"

#include "Cader/Utility/Assert.h"

#include "Instance.h"
#include "Utility.h"

#include <string>
#include <vector>

namespace CDR::VK {

	static constexpr std::array<Text, 1> RequiredExtensions
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	bool QueueFamilyIndicies::IsComplete() const noexcept
	{
		return graphicsFamilyIndex >= 0 && presentFamilyIndex >= 0 && transferFamilyIndex >= 0;
	}

	u8 QueueFamilyIndicies::GetUniqueFamilyIndicies(std::array<i8, 3>& pIndicies) const
	{
		u8 count = 0;

		pIndicies[count++] = graphicsFamilyIndex;

		if(presentFamilyIndex != graphicsFamilyIndex)
			pIndicies[count++] = presentFamilyIndex;

		if(transferFamilyIndex != graphicsFamilyIndex)
			pIndicies[count++] = transferFamilyIndex;

		return count;
	}

	Device::Device(const Instance& pInstance)
		: mInstance{pInstance}
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
		CDR_ASSERT(physicalDevicesCount);

		std::vector<VkPhysicalDevice> physicalDevices(physicalDevicesCount);
		VK_VERIFY(vkEnumeratePhysicalDevices(mInstance.GetInstance(), &physicalDevicesCount, &physicalDevices[0]));

		struct PhysicalDeviceRating final
		{
			QueueFamilyIndicies queueFamilyIndicies;
			u8 index{0};
			u8 score{0};
		};

		PhysicalDeviceRating physicalDeviceRating;

		for(u8 i = 0; i < (u8)physicalDevicesCount; i++)
		{
			QueueFamilyIndicies queueFamilyIndicies;
			const u8 score = RatePhysicalDevice(physicalDevices[i], &queueFamilyIndicies);

			if(score > physicalDeviceRating.score)
			{
				physicalDeviceRating.index = i;
				physicalDeviceRating.score = score;
				physicalDeviceRating.queueFamilyIndicies = queueFamilyIndicies;
			}
		}

		CDR_ASSERT(physicalDeviceRating.score);

		mPhysicalDevice = physicalDevices[physicalDeviceRating.index];
		vkGetPhysicalDeviceMemoryProperties(mPhysicalDevice, &mMemoryProperties);
		mQueueFamilyIndicies = physicalDeviceRating.queueFamilyIndicies;
	}

	u8 Device::RatePhysicalDevice(const VkPhysicalDevice pPhysicalDevice, QueueFamilyIndicies* pQueueFamilyIndicies) const
	{
		u32 score = 0;

		u32 extensionsCount;
		VK_VERIFY(vkEnumerateDeviceExtensionProperties(pPhysicalDevice, nullptr, &extensionsCount, nullptr));

		if(extensionsCount <= 0)
			return 0;

		std::vector<VkExtensionProperties> extensions(extensionsCount);
		VK_VERIFY(vkEnumerateDeviceExtensionProperties(pPhysicalDevice, nullptr, &extensionsCount, &extensions[0]));

		u8 extensionsFound = 0;

		for(u8 i = 0; i < (u8)RequiredExtensions.size(); i++)
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

		if(extensionsFound != (u8)RequiredExtensions.size())
			return 0;

		u32 queueFamilyPropertiesCount;
		vkGetPhysicalDeviceQueueFamilyProperties(pPhysicalDevice, &queueFamilyPropertiesCount, nullptr);

		if(queueFamilyPropertiesCount <= 0)
			return 0;

		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertiesCount);
		vkGetPhysicalDeviceQueueFamilyProperties(pPhysicalDevice, &queueFamilyPropertiesCount, &queueFamilyProperties[0]);

		for(u8 i = 0; i < (u8)queueFamilyPropertiesCount; i++)
		{
			if(pQueueFamilyIndicies->graphicsFamilyIndex < 0 && queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				pQueueFamilyIndicies->graphicsFamilyIndex = i;
				goto ASSIGNED;
			}

			if(pQueueFamilyIndicies->presentFamilyIndex < 0)
			{
				u32 surfaceSupported;
				VK_VERIFY(vkGetPhysicalDeviceSurfaceSupportKHR(pPhysicalDevice, i, mInstance.GetSurface(), &surfaceSupported));

				if(surfaceSupported)
				{
					pQueueFamilyIndicies->presentFamilyIndex = i;
					goto ASSIGNED;
				}
			}

			if(pQueueFamilyIndicies->transferFamilyIndex < 0 && queueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				pQueueFamilyIndicies->transferFamilyIndex = i;
				goto ASSIGNED;
			}

		ASSIGNED:
			if(pQueueFamilyIndicies->IsComplete())
				break;
		}

		if(pQueueFamilyIndicies->graphicsFamilyIndex < 0)
			return 0;

		if(pQueueFamilyIndicies->presentFamilyIndex < 0)
			pQueueFamilyIndicies->presentFamilyIndex = pQueueFamilyIndicies->graphicsFamilyIndex;
		else
			score++;

		if(pQueueFamilyIndicies->transferFamilyIndex < 0)
			pQueueFamilyIndicies->transferFamilyIndex = pQueueFamilyIndicies->graphicsFamilyIndex;
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
		std::array<i8, 3> uniqueQueueFamilies;
		const u8 uniqueQueueFamiliesCount = mQueueFamilyIndicies.GetUniqueFamilyIndicies(uniqueQueueFamilies);

		std::array<VkDeviceQueueCreateInfo, 3> queueCreateInfos{};

		constexpr float queuePriority = 1.0f;

		for(u8 i = 0; i < uniqueQueueFamiliesCount; i++)
		{
			queueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfos[i].pQueuePriorities = &queuePriority;
			queueCreateInfos[i].queueFamilyIndex = uniqueQueueFamilies[i];
			queueCreateInfos[i].queueCount = 1;
		}

		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo deviceInfo = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
		deviceInfo.enabledExtensionCount = (u8)RequiredExtensions.size();
		deviceInfo.ppEnabledExtensionNames = &RequiredExtensions[0];

		deviceInfo.queueCreateInfoCount = uniqueQueueFamiliesCount;
		deviceInfo.pQueueCreateInfos = &queueCreateInfos[0];

		deviceInfo.pEnabledFeatures = &deviceFeatures;

		VK_VERIFY(vkCreateDevice(mPhysicalDevice, &deviceInfo, nullptr, &mDevice));

		vkGetDeviceQueue(mDevice, mQueueFamilyIndicies.graphicsFamilyIndex, 0, &mGraphicsQueue);
		vkGetDeviceQueue(mDevice, mQueueFamilyIndicies.presentFamilyIndex, 0, &mPresentQueue);
		vkGetDeviceQueue(mDevice, mQueueFamilyIndicies.transferFamilyIndex, 0, &mTransferQueue);
	}

	void Device::WaitIdle()
	{
		VK_VERIFY(vkDeviceWaitIdle(mDevice));
	}

}