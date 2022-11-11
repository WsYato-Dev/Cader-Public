#include "Sync.h"

#include "Device.h"
#include "SwapChain.h"
#include "Utility.h"

namespace CDR::VK {

	Sync::Sync(const Device& pDevice, const SwapChain& pSwapChain)
		: mDevice{pDevice}
	{
		const u8 syncObjectsCount = pSwapChain.GetMaxFramesInFlight();

		InitSemaphores(syncObjectsCount);
		InitFences(syncObjectsCount);
	}

	Sync::~Sync()
	{
		for(const auto& fence : mInFlightFrames)
			vkDestroyFence(mDevice.GetDevice(), fence, nullptr);

		for(const auto& semaphore : mRenderingDone)
			vkDestroySemaphore(mDevice.GetDevice(), semaphore, nullptr);

		for(const auto& semaphore : mImageAcquired)
			vkDestroySemaphore(mDevice.GetDevice(), semaphore, nullptr);
	}

	void Sync::InitSemaphores(u8 pFramesInFlightCount)
	{
		mImageAcquired.resize(pFramesInFlightCount);
		mRenderingDone.resize(pFramesInFlightCount);

		VkSemaphoreCreateInfo semaphoreInfo = {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};

		for(u8 i = 0; i < pFramesInFlightCount; i++)
		{
			VK_VERIFY(vkCreateSemaphore(mDevice.GetDevice(), &semaphoreInfo, nullptr, &mImageAcquired[i]));
			VK_VERIFY(vkCreateSemaphore(mDevice.GetDevice(), &semaphoreInfo, nullptr, &mRenderingDone[i]));
		}
	}

	void Sync::InitFences(u8 pFramesInFlightCount)
	{
		mInFlightFrames.resize(pFramesInFlightCount);

		VkFenceCreateInfo fenceInfo = {VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for(u8 i = 0; i < pFramesInFlightCount; i++)
			VK_VERIFY(vkCreateFence(mDevice.GetDevice(), &fenceInfo, nullptr, &mInFlightFrames[i]));
	}

}