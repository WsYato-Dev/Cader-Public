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
			Sync(const Device& pDevice, const SwapChain& pSwapChain);
			~Sync();

			void InitSemaphores(const u8 pFramesInFlightCount);
			void InitFences(const u8 pFramesInFlightCount);

		public:
			const std::vector<VkSemaphore>& GetImageAcquired() const noexcept { return mImageAcquired; }
			const std::vector<VkSemaphore>& GetRenderingDone() const noexcept { return mRenderingDone; }

			const std::vector<VkFence>& GetInFlightFrames() const noexcept { return mInFlightFrames; }

		private:
			const Device& mDevice;

			std::vector<VkSemaphore> mImageAcquired;
			std::vector<VkSemaphore> mRenderingDone;

			std::vector<VkFence> mInFlightFrames;

			friend Graphics;
		};

	}

}