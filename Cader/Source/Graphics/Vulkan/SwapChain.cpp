#include "SwapChain.h"

#include "Cader/Utility/Assert.h"
#include "Device.h"
#include "Instance.h"
#include "Utility.h"

namespace CDR::VK {

	SwapChain::SwapChain(const Instance& pInstance, const Device& pDevice)
		: mInstance{pInstance}
		, mDevice{pDevice}
	{
		InitStaticInfo();
		CreateSwapChain((u16)mStaticInfo.surfaceCapabilities.currentExtent.width, (u16)mStaticInfo.surfaceCapabilities.currentExtent.height);
	}

	SwapChain::~SwapChain()
	{
		DestroySwapChain();
	}

	void SwapChain::InitStaticInfo()
	{
		VK_VERIFY(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(mDevice.GetPhysicalDevice(), mInstance.GetSurface(), &mStaticInfo.surfaceCapabilities));

		mStaticInfo.imageCount = mStaticInfo.surfaceCapabilities.minImageCount + 1;

		if(0 < mStaticInfo.surfaceCapabilities.maxImageCount && mStaticInfo.surfaceCapabilities.maxImageCount < mStaticInfo.imageCount)
			mStaticInfo.imageCount = mStaticInfo.surfaceCapabilities.maxImageCount;

		u32 surfaceFormatsCount;
		VK_VERIFY(vkGetPhysicalDeviceSurfaceFormatsKHR(mDevice.GetPhysicalDevice(), mInstance.GetSurface(), &surfaceFormatsCount, nullptr));
		CDR_ASSERT(surfaceFormatsCount);

		std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatsCount);
		VK_VERIFY(vkGetPhysicalDeviceSurfaceFormatsKHR(mDevice.GetPhysicalDevice(), mInstance.GetSurface(), &surfaceFormatsCount, &surfaceFormats[0]));

		bool desiredFormatFount = false;

		for(u32 i = 0; i < surfaceFormatsCount; i++)
		{
			if(VK_FORMAT_B8G8R8A8_UNORM == surfaceFormats[i].format && VK_COLOR_SPACE_SRGB_NONLINEAR_KHR == surfaceFormats[i].colorSpace)
			{
				mStaticInfo.surfaceFormat = surfaceFormats[i];
				desiredFormatFount = true;
				break;
			}
		}

		if(!desiredFormatFount)
			mStaticInfo.surfaceFormat = surfaceFormats[0];

		mImages.resize(mStaticInfo.imageCount);
		mImageViews.resize(mStaticInfo.imageCount);

		mMaxFramesInFlight = DesiredFramesInFlight < mStaticInfo.imageCount ? DesiredFramesInFlight : mStaticInfo.imageCount;
	}

	void SwapChain::CreateSwapChain(const u16 pWidth, const u16 pHeight)
	{
		if(!mSwapChainDestroyed)
			return;

		InitSwapChain(pWidth, pHeight);
		InitSwapChainImageViews();

		mSwapChainDestroyed = false;
	}

	void SwapChain::DestroySwapChain()
	{
		if(mSwapChainDestroyed)
			return;

		for(const auto& view : mImageViews)
			vkDestroyImageView(mDevice.GetDevice(), view, nullptr);

		vkDestroySwapchainKHR(mDevice.GetDevice(), mSwapChain, nullptr);

		mSwapChainDestroyed = true;
	}

	void SwapChain::InitSwapChain(const u16 pWidth, const u16 pHeight)
	{
		mExtent = {pWidth, pHeight};

		VkSwapchainCreateInfoKHR swapChainInfo = {VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR};
		swapChainInfo.surface = mInstance.GetSurface();

		swapChainInfo.imageExtent = mExtent;
		swapChainInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;

		swapChainInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
		swapChainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

		swapChainInfo.minImageCount = mStaticInfo.imageCount;
		swapChainInfo.imageFormat = mStaticInfo.surfaceFormat.format;
		swapChainInfo.imageColorSpace = mStaticInfo.surfaceFormat.colorSpace;

		swapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapChainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		swapChainInfo.imageArrayLayers = 1;
		swapChainInfo.clipped = true;

		VK_VERIFY(vkCreateSwapchainKHR(mDevice.GetDevice(), &swapChainInfo, nullptr, &mSwapChain));

		u32 imagesCount = mStaticInfo.imageCount;
		VK_VERIFY(vkGetSwapchainImagesKHR(mDevice.GetDevice(), mSwapChain, &imagesCount, &mImages[0]));
	}

	void SwapChain::InitSwapChainImageViews()
	{
		VkImageViewCreateInfo viewInfo = {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};

		viewInfo.format = mStaticInfo.surfaceFormat.format;
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;

		viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.layerCount = 1;

		for(u8 i = 0; i < mStaticInfo.imageCount; i++)
		{
			viewInfo.image = mImages[i];
			VK_VERIFY(vkCreateImageView(mDevice.GetDevice(), &viewInfo, nullptr, &mImageViews[i]));
		}
	}

}