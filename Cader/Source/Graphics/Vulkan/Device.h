#pragma once

#include "Cader/Types/Common.h"

#include <array>

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;

	namespace VK {

		class Instance;

		struct QueueFamilyIndicies final
		{
			bool IsComplete() const noexcept;
			u8 GetUniqueFamilyIndicies(std::array<i8, 3>& pIndicies) const;

			i8 graphicsFamilyIndex{-1};
			i8 presentFamilyIndex{-1};
			i8 transferFamilyIndex{-1};
		};

		class Device final
		{
			Device(const Instance& pInstance);
			~Device();

			void InitPhysicalDevice();
			u8 RatePhysicalDevice(const VkPhysicalDevice pPhysicalDevice, QueueFamilyIndicies* pQueueFamilyIndicies) const;

			void InitDevice();

		public:
			void WaitIdle();

			const VkPhysicalDevice GetPhysicalDevice() const noexcept { return mPhysicalDevice; }
			const VkPhysicalDeviceMemoryProperties& GetMemoryProperties() const noexcept { return mMemoryProperties; }
			QueueFamilyIndicies GetQueueFamilyIndicies() const noexcept { return mQueueFamilyIndicies; }

			const VkDevice GetDevice() const noexcept { return mDevice; }

			const VkQueue GetGraphicsQueue() const noexcept { return mGraphicsQueue; }
			const VkQueue GetPresentQueue() const noexcept { return mPresentQueue; }
			const VkQueue GetTransferQueue() const noexcept { return mTransferQueue; }

		private:
			const Instance& mInstance;

			VkPhysicalDevice mPhysicalDevice;
			VkPhysicalDeviceMemoryProperties mMemoryProperties;
			QueueFamilyIndicies mQueueFamilyIndicies;

			VkDevice mDevice;

			VkQueue mGraphicsQueue;
			VkQueue mPresentQueue;
			VkQueue mTransferQueue;

			friend Graphics;
		};

	}

}