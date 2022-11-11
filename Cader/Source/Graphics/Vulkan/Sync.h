#pragma once

#include "Cader/Types/Common.h"

#include <vector>

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;

	namespace VK {

		class Device;
		class SwapChain;

		class Sync final
		{
			friend Graphics;

			const Device& mDevice;

			std::vector<VkSemaphore> mImageAcquired;
			std::vector<VkSemaphore> mRenderingDone;

			std::vector<VkFence> mInFlightFrames;

			Sync(const Device& pDevice, const SwapChain& pSwapChain);
			~Sync();

			void InitSemaphores(u8 pFramesInFlightCount);
			void InitFences(u8 pFramesInFlightCount);

		public:
			inline const std::vector<VkSemaphore>& GetImageAcquired() const noexcept { return mImageAcquired; }
			inline const std::vector<VkSemaphore>& GetRenderingDone() const noexcept { return mRenderingDone; }

			inline const std::vector<VkFence>& GetInFlightFrames() const noexcept { return mInFlightFrames; }
		};

	}

}