#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;

	namespace VK {

		class Device;
		class SwapChain;

		class Commands final
		{
			friend Graphics;

			const Device& mDevice;

			VkCommandPool mGraphicsCommandPool;
			VkCommandPool mTransferCommandPool;

			std::vector<VkCommandBuffer> mGraphicsCommandBuffers;

			Commands(const Device& pDevice, const SwapChain& pSwapChain);
			~Commands();

			void InitCommandPools();
			void InitGraphicsCommandBuffers(const SwapChain& pSwapChain);

		public:
			inline const VkCommandPool& GetGraphicsCommandPool() const noexcept { return mGraphicsCommandPool; }
			inline const VkCommandPool& GetTransferCommandPool() const noexcept { return mTransferCommandPool; }

			inline const std::vector<VkCommandBuffer>& GetGraphicsCommandBuffers() const noexcept { return mGraphicsCommandBuffers; }
		};

	}

}