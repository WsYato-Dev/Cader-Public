#include "RenderPass.h"

#include "Device.h"
#include "SwapChain.h"
#include "Utility.h"

namespace CDR::VK {

	RenderPass::RenderPass(const Device& pDevice, const SwapChain& pSwapChain)
		: mDevice(pDevice)
		, mSwapChain(pSwapChain)
	{
		InitRenderPass(pSwapChain);

		mFrameBuffers.resize(pSwapChain.GetStaticInfo().imageCount);

		const VkExtent2D swapChainExtent = pSwapChain.GetExtent();
		CreateFrameBuffers((u16)swapChainExtent.width, (u16)swapChainExtent.height);
	}

	RenderPass::~RenderPass()
	{
		DestroyFrameBuffers();
		vkDestroyRenderPass(mDevice.GetDevice(), mRenderPass, nullptr);
	}

	void RenderPass::InitRenderPass(const SwapChain& pSwapChain)
	{
		VkAttachmentDescription colorAttachment = {};
		colorAttachment.format = pSwapChain.GetStaticInfo().surfaceFormat.format;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;

		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentReference = {};
		colorAttachmentReference.attachment = 0;
		colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subPassDescription = {};
		subPassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

		subPassDescription.colorAttachmentCount = 1;
		subPassDescription.pColorAttachments = &colorAttachmentReference;

		VkRenderPassCreateInfo renderPassInfo = {VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;

		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subPassDescription;

		renderPassInfo.dependencyCount = 0;
		renderPassInfo.pDependencies = nullptr;

		VK_VERIFY(vkCreateRenderPass(mDevice.GetDevice(), &renderPassInfo, nullptr, &mRenderPass));
	}

	void RenderPass::CreateFrameBuffers(u16 pWidth, u16 pHeight)
	{
		if(!mDestroyed)
			return;

		VkFramebufferCreateInfo frameBufferInfo = {VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
		frameBufferInfo.renderPass = mRenderPass;
		frameBufferInfo.height = pHeight;
		frameBufferInfo.width = pWidth;

		frameBufferInfo.attachmentCount = 1;
		frameBufferInfo.layers = 1;

		for(u8 i = 0; i < (u8)mFrameBuffers.size(); i++)
		{
			frameBufferInfo.pAttachments = &mSwapChain.GetImagesViews()[i];
			VK_VERIFY(vkCreateFramebuffer(mDevice.GetDevice(), &frameBufferInfo, nullptr, &mFrameBuffers[i]));
		}

		mDestroyed = false;
	}

	void RenderPass::DestroyFrameBuffers()
	{
		if(mDestroyed)
			return;

		for(const auto& buffer : mFrameBuffers)
			vkDestroyFramebuffer(mDevice.GetDevice(), buffer, nullptr);

		mDestroyed = true;
	}

}