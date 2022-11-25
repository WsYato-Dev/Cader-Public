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
			Commands(const Device& pDevice, const SwapChain& pSwapChain);
			~Commands();

			void InitCommandPools();
			void InitGraphicsCommandBuffers(const SwapChain& pSwapChain);

		public:
			const VkCommandPool GetGraphicsCommandPool() const noexcept { return mGraphicsCommandPool; }
			const VkCommandPool GetTransferCommandPool() const noexcept { return mTransferCommandPool; }

			const std::vector<VkCommandBuffer>& GetGraphicsCommandBuffers() const noexcept { return mGraphicsCommandBuffers; }

		private:
			const Device& mDevice;

			VkCommandPool mGraphicsCommandPool;
			VkCommandPool mTransferCommandPool;

			std::vector<VkCommandBuffer> mGraphicsCommandBuffers;

			friend Graphics;
		};

	}

}