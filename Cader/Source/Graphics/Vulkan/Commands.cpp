#include "Commands.h"

#include "Cader/Types/Common.h"

#include "Device.h"
#include "SwapChain.h"
#include "Utility.h"

namespace CDR::VK {

	Commands::Commands(const Device& pDevice, const SwapChain& pSwapChain)
		: mDevice{pDevice}
	{
		InitCommandPools();
		InitGraphicsCommandBuffers(pSwapChain);
	}

	Commands::~Commands()
	{
		vkFreeCommandBuffers(mDevice.GetDevice(), mGraphicsCommandPool, (u8)mGraphicsCommandBuffers.size(), &mGraphicsCommandBuffers[0]);

		vkDestroyCommandPool(mDevice.GetDevice(), mTransferCommandPool, nullptr);
		vkDestroyCommandPool(mDevice.GetDevice(), mGraphicsCommandPool, nullptr);
	}

	void Commands::InitCommandPools()
	{
		const QueueFamilyIndicies queueFamilyIndicies = mDevice.GetQueueFamilyIndicies();

		VkCommandPoolCreateInfo commandPoolInfo = {VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
		commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		commandPoolInfo.queueFamilyIndex = queueFamilyIndicies.graphicsFamilyIndex;

		VK_VERIFY(vkCreateCommandPool(mDevice.GetDevice(), &commandPoolInfo, nullptr, &mGraphicsCommandPool));

		commandPoolInfo.flags = 0;
		commandPoolInfo.queueFamilyIndex = queueFamilyIndicies.transferFamilyIndex;

		VK_VERIFY(vkCreateCommandPool(mDevice.GetDevice(), &commandPoolInfo, nullptr, &mTransferCommandPool));
	}

	void Commands::InitGraphicsCommandBuffers(const SwapChain& pSwapChain)
	{
		const u8 commandBuffersCount = pSwapChain.GetMaxFramesInFlight();

		mGraphicsCommandBuffers.resize(commandBuffersCount);

		VkCommandBufferAllocateInfo commandBufferInfo = {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
		commandBufferInfo.commandPool = mGraphicsCommandPool;
		commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferInfo.commandBufferCount = commandBuffersCount;

		VK_VERIFY(vkAllocateCommandBuffers(mDevice.GetDevice(), &commandBufferInfo, &mGraphicsCommandBuffers[0]));
	}

}