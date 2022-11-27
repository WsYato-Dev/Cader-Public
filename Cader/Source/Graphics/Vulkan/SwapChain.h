#pragma once

#include "Cader/Types/Common.h"

#include <vector>

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;

	namespace VK {

		class Device;
		class Instance;

		constexpr u8 DesiredFramesInFlight{3};

		struct SwapChainStaticInfo final
		{
			VkSurfaceCapabilitiesKHR surfaceCapabilities;
			VkSurfaceFormatKHR surfaceFormat;
			u8 imageCount{0};
		};

		class SwapChain final
		{
			SwapChain(const Instance& pInstance, const Device& pDevice);
			~SwapChain();

			void InitStaticInfo();

			void CreateSwapChain(u16 pWidth, u16 pHeight);
			void DestroySwapChain();

			void InitSwapChain(u16 pWidth, u16 pHeight);
			void InitSwapChainImageViews();

		public:
			const SwapChainStaticInfo& GetStaticInfo() const noexcept { return mStaticInfo; }

			const VkSwapchainKHR GetSwapChain() const noexcept { return mSwapChain; }
			const std::vector<VkImage>& GetImages() const noexcept { return mImages; }
			const std::vector<VkImageView>& GetImagesViews() const noexcept { return mImageViews; }
			VkExtent2D GetExtent() const noexcept { return mExtent; }

			u8 GetMaxFramesInFlight() const noexcept { return mMaxFramesInFlight; }

		private:
			const Instance& mInstance;
			const Device& mDevice;

			SwapChainStaticInfo mStaticInfo;

			VkSwapchainKHR mSwapChain;
			std::vector<VkImage> mImages;
			std::vector<VkImageView> mImageViews;
			VkExtent2D mExtent;

			u8 mMaxFramesInFlight{0};

			bool mSwapChainDestroyed{true};

			friend Graphics;
		};

	}

}