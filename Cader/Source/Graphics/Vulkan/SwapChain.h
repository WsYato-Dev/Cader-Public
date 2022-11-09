#pragma once

#include "Cader/Types/Common.h"

#include <vector>

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;

	namespace VK {

		class Device;
		class Instance;

		constexpr u8 DesiredFramesInFlight = 3;

		struct SwapChainStaticInfo final
		{
			VkSurfaceCapabilitiesKHR surfaceCapabilities;
			VkSurfaceFormatKHR surfaceFormat;
			u8 imageCount = 0;
		};

		class SwapChain final
		{
			friend Graphics;

			const Instance& mInstance;
			const Device& mDevice;

			SwapChainStaticInfo mStaticInfo = {};

			VkSwapchainKHR mSwapChain;
			std::vector<VkImage> mImages;
			std::vector<VkImageView> mImageViews;
			VkExtent2D mExtent;

			u8 mMaxFramesInFlight = 0;

			bool mDestroyed = true;

			SwapChain(const Instance& pInstance, const Device& pDevice);
			~SwapChain();

			void InitStaticInfo();

			void CreateSwapChain(u16 pWidth, u16 pHeight);
			void DestroySwapChain();

			void InitSwapChain(u16 pWidth, u16 pHeight);
			void InitSwapChainImageViews();

		public:
			inline const SwapChainStaticInfo& GetStaticInfo() const noexcept { return mStaticInfo; }

			inline const VkSwapchainKHR& GetSwapChain() const noexcept { return mSwapChain; }
			inline const std::vector<VkImage>& GetImages() const noexcept { return mImages; }
			inline const std::vector<VkImageView>& GetImagesViews() const noexcept { return mImageViews; }
			inline VkExtent2D GetExtent() const noexcept { return mExtent; }

			inline u8 GetMaxFramesInFlight() const noexcept { return mMaxFramesInFlight; }
		};

	}

}