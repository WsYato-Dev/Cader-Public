#include "Cader/Graphics/Graphics.h"

#include "Cader/Core/Engine.h"
#include "Cader/Window/Window.h"
#include "Cader/Window/WindowSettings.h"

#include "Vulkan/Commands.h"
#include "Vulkan/Device.h"
#include "Vulkan/Instance.h"
#include "Vulkan/RenderPass.h"
#include "Vulkan/SwapChain.h"
#include "Vulkan/Sync.h"
#include "Vulkan/Utility.h"

#include <stdint.h>

#include <vulkan/vulkan.h>

namespace CDR {

	Graphics::Graphics(const Window& pWindow, const StartupSettings& pStartupSettings)
		: clearColor{pStartupSettings.windowClearColor}
	{
		mInstance = new VK::Instance(pWindow);
		mDevice = new VK::Device(*mInstance);
		mSwapChain = new VK::SwapChain(*mInstance, *mDevice);
		mRenderPass = new VK::RenderPass(*mDevice, *mSwapChain);
		mSync = new VK::Sync(*mDevice, *mSwapChain);
		mCommands = new VK::Commands(*mDevice, *mSwapChain);
	}

	Graphics::~Graphics()
	{
		mDevice->WaitIdle();

		delete mCommands;
		delete mSync;
		delete mRenderPass;
		delete mSwapChain;
		delete mDevice;
		delete mInstance;
	}

	void Graphics::NewFrame()
	{
		if(!mCanRender)
			return;

		const VkDevice device = mDevice->GetDevice();
		const VkFence fence = mSync->GetInFlightFrames()[mInFlightFrameIndex];

		VK_VERIFY(vkWaitForFences(device, 1, &fence, true, UINT64_MAX));
		VK_VERIFY(vkResetFences(device, 1, &fence));

		VK_VERIFY(vkAcquireNextImageKHR(device, mSwapChain->GetSwapChain(), UINT64_MAX, mSync->GetImageAcquired()[mInFlightFrameIndex], nullptr, &mSwapChainImageIndex));

		const VkCommandBuffer commandBuffer = mCommands->GetGraphicsCommandBuffers()[mInFlightFrameIndex];
		constexpr VkCommandBufferBeginInfo commandbufferBeginInfo = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};

		VK_VERIFY(vkBeginCommandBuffer(commandBuffer, &commandbufferBeginInfo));

		const VkClearValue clearValue = {clearColor.r, clearColor.g, clearColor.b, 1.0f};
		const VkRect2D rect = {{0, 0}, mSwapChain->GetExtent()};

		VkRenderPassBeginInfo renderPassBeginInfo = {VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
		renderPassBeginInfo.renderPass = mRenderPass->GetRenderPass();
		renderPassBeginInfo.framebuffer = mRenderPass->GetFrameBuffers()[mSwapChainImageIndex];

		renderPassBeginInfo.clearValueCount = 1;
		renderPassBeginInfo.pClearValues = &clearValue;

		renderPassBeginInfo.renderArea = rect;

		vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	void Graphics::RenderFrame()
	{
		if(!mCanRender)
			return;

		const VkCommandBuffer commandBuffer = mCommands->GetGraphicsCommandBuffers()[mInFlightFrameIndex];

		vkCmdEndRenderPass(commandBuffer);
		VK_VERIFY(vkEndCommandBuffer(commandBuffer));

		constexpr VkPipelineStageFlags waitStages[1] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
		const VkSemaphore signalSemaphore = mSync->GetRenderingDone()[mInFlightFrameIndex];

		VkSubmitInfo submitInfo = {VK_STRUCTURE_TYPE_SUBMIT_INFO};
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &mSync->GetImageAcquired()[mInFlightFrameIndex];

		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &signalSemaphore;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		VK_VERIFY(vkQueueSubmit(mDevice->GetGraphicsQueue(), 1, &submitInfo, mSync->GetInFlightFrames()[mInFlightFrameIndex]));

		VkPresentInfoKHR presentInfo = {VK_STRUCTURE_TYPE_PRESENT_INFO_KHR};
		presentInfo.pImageIndices = &mSwapChainImageIndex;

		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &mSwapChain->GetSwapChain();

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &signalSemaphore;

		const VkResult result = vkQueuePresentKHR(mDevice->GetPresentQueue(), &presentInfo);

		if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
			return;

		VK_VERIFY(result);

		if(++mInFlightFrameIndex >= mSwapChain->GetMaxFramesInFlight())
			mInFlightFrameIndex = 0;
	}

	void Graphics::OnWindowMinimize(Event pEvent)
	{
		if(pEvent.windowMinimized)
		{
			mDevice->WaitIdle();

			mRenderPass->DestroyFrameBuffers();
			mSwapChain->DestroySwapChain();

			mCanRender = false;
		}
		else
		{
			const WindowSize size = Engine::Get().GetWindow().GetSize();

			mSwapChain->CreateSwapChain(size.width, size.height);
			mRenderPass->CreateFrameBuffers(size.width, size.height);

			mCanRender = true;
		}
	}

	void Graphics::OnWindowResize(Event pEvent)
	{
		mDevice->WaitIdle();

		mSwapChain->DestroySwapChain();
		mRenderPass->DestroyFrameBuffers();

		mSwapChain->CreateSwapChain(pEvent.windowSize.width, pEvent.windowSize.height);
		mRenderPass->CreateFrameBuffers(pEvent.windowSize.width, pEvent.windowSize.height);
	}

}