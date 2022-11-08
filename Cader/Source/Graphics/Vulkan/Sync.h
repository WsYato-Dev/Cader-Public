#pragma once

#include "Cader/Types/Common.h"

#include <vector>

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;

	namespace VK {

		class Device;
		class SwapChain;

		constexpr u8 MaxFramesInFlight = 3;

		class Sync final
		{
			friend Graphics;

			const Device& mDevice;

			std::vector<VkSemaphore> mImageAquired;
			std::vector<VkSemaphore> mRenderingDone;

			std::vector<VkFence> mInFlightFrames;

			Sync(const Device& pDevice, const SwapChain& pSwapChain);
			~Sync();

			void InitSemaphores(u8 pFramesInFlightCount);
			void InitFences(u8 pFramesInFlightCount);

		public:
			inline const std::vector<VkSemaphore>& GetImageAquired() const noexcept { return mImageAquired; }
			inline const std::vector<VkSemaphore>& GetRenderingDone() const noexcept { return mRenderingDone; }

			inline const std::vector<VkFence>& GetInFlightFrames() const noexcept { return mInFlightFrames; }
		};

	}

}