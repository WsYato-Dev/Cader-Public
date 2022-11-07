#pragma once

#include "Cader/Types/Common.h"

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;

	namespace VK {

		class Instance;

		struct QueueIndicies final
		{
			i8 graphicsIndex = -1;
			i8 presentIndex = -1;
			i8 transferIndex = -1;

			bool IsComplete() const noexcept;
			u8 GetUniqueIndicies(i8 pIndicies[3]) const;
		};

		class Device final
		{
			friend Graphics;

			const Instance& mInstance;

			VkPhysicalDevice mPhysicalDevice = nullptr;
			QueueIndicies mQueueIndicies = {};

			VkDevice mDevice = nullptr;

			VkQueue mGraphicsQueue = nullptr;
			VkQueue mPresentQueue = nullptr;
			VkQueue mTransferQueue = nullptr;

			Device(const Instance& pInstance);
			~Device();

			void InitPhysicalDevice();
			u8 RatePhysicalDevice(const VkPhysicalDevice& pPhysicalDevice, QueueIndicies& pQueueIndicies) const;

			void InitDevice();

		public:
			void WaitIdle();

			inline const VkPhysicalDevice& GetPhysicalDevice() const noexcept { return mPhysicalDevice; }

			inline const VkDevice& GetDevice() const noexcept { return mDevice; }

			inline const VkQueue& GetGraphicsQueue() const noexcept { return mGraphicsQueue; }
			inline const VkQueue& GetPresentQueue() const noexcept { return mPresentQueue; }
			inline const VkQueue& GetTransferQueue() const noexcept { return mTransferQueue; }
		};

	}

}