#pragma once

#include "Cader/Types/Common.h"

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;

	namespace VK {

		class Instance;

		struct QueueFamilyIndicies final
		{
			i8 graphicsFamilyIndex = -1;
			i8 presentFamilyIndex = -1;
			i8 transferFamilyIndex = -1;

			bool IsComplete() const noexcept;
			u8 GetUniqueFamilyIndicies(i8 pIndicies[3]) const;
		};

		class Device final
		{
			friend Graphics;

			const Instance& mInstance;

			VkPhysicalDevice mPhysicalDevice;
			QueueFamilyIndicies mQueueFamilyIndicies = {};

			VkDevice mDevice;

			VkQueue mGraphicsQueue;
			VkQueue mPresentQueue;
			VkQueue mTransferQueue;

			Device(const Instance& pInstance);
			~Device();

			void InitPhysicalDevice();
			u8 RatePhysicalDevice(const VkPhysicalDevice& pPhysicalDevice, QueueFamilyIndicies& pQueueFamilyIndicies) const;

			void InitDevice();

		public:
			void WaitIdle();

			inline const VkPhysicalDevice& GetPhysicalDevice() const noexcept { return mPhysicalDevice; }
			inline QueueFamilyIndicies GetQueueFamilyIndicies() const noexcept { return mQueueFamilyIndicies; }

			inline const VkDevice& GetDevice() const noexcept { return mDevice; }

			inline const VkQueue& GetGraphicsQueue() const noexcept { return mGraphicsQueue; }
			inline const VkQueue& GetPresentQueue() const noexcept { return mPresentQueue; }
			inline const VkQueue& GetTransferQueue() const noexcept { return mTransferQueue; }
		};

	}

}