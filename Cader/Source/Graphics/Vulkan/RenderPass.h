#pragma once

#include "Cader/Types/Common.h"

#include <vector>

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;

	namespace VK {

		class Device;
		class SwapChain;

		class RenderPass final
		{
			friend Graphics;

			const Device& mDevice;
			const SwapChain& mSwapChain;

			VkRenderPass mRenderPass;
			std::vector<VkFramebuffer> mFrameBuffers;

			bool mFrameBuffersDestroyed{true};

			RenderPass(const Device& pDevice, const SwapChain& pSwapChain);
			~RenderPass();

			void InitRenderPass();

			void CreateFrameBuffers(u16 pWidth, u16 pHeight);
			void DestroyFrameBuffers();

		public:
			inline const VkRenderPass& GetRenderPass() const noexcept { return mRenderPass; }
			inline const std::vector<VkFramebuffer>& GetFrameBuffers() const noexcept { return mFrameBuffers; }
		};

	}

}