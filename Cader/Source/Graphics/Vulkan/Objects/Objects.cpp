#include "Objects.h"

#include "../Commands.h"
#include "../Device.h"
#include "../Utility.h"

namespace CDR::VK {

	const Device* Objects::sDevice{nullptr};
	const Commands* Objects::sCommands{nullptr};

	void Objects::Init(const Device* pDevice, const Commands* pCommands)
	{
		sDevice = pDevice;
		sCommands = pCommands;
	}

	VkResult Objects::CreateBuffer(const VkBufferCreateInfo& pCreateInfo, VkBuffer* pBuffer)
	{
		return vkCreateBuffer(sDevice->GetDevice(), &pCreateInfo, nullptr, pBuffer);
	}

	void Objects::DestroyBuffer(const VkBuffer pBuffer)
	{
		vkDestroyBuffer(sDevice->GetDevice(), pBuffer, nullptr);
	}

	void Objects::GetBufferMemoryRequirements(const VkBuffer pBuffer, VkMemoryRequirements* pMemoryRequirements)
	{
		vkGetBufferMemoryRequirements(sDevice->GetDevice(), pBuffer, pMemoryRequirements);
	}

	VkResult Objects::BindBufferMemory(const VkBuffer pBuffer, const VkDeviceMemory pMemory)
	{
		return vkBindBufferMemory(sDevice->GetDevice(), pBuffer, pMemory, 0);
	}

	u32 Objects::FindMemoryType(u32 pFilter, VkMemoryPropertyFlags pMemoryProperties)
	{
		const VkPhysicalDeviceMemoryProperties& memoryProperties = sDevice->GetMemoryProperties();

		for(u32 i = 0; i < memoryProperties.memoryTypeCount; i++)
			if((pFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & pMemoryProperties) == pMemoryProperties)
				return i;

		return 0;
	}

	VkResult Objects::AllocateMemory(const VkMemoryAllocateInfo& pAllocateInfo, VkDeviceMemory* pMemory)
	{
		return vkAllocateMemory(sDevice->GetDevice(), &pAllocateInfo, nullptr, pMemory);
	}

	void Objects::FreeMemory(const VkDeviceMemory pMemory)
	{
		vkFreeMemory(sDevice->GetDevice(), pMemory, nullptr);
	}

	VkResult Objects::MapMemory(const VkDeviceMemory pMemory, u32 pOffset, u32 pSize, VkMemoryMapFlags pMapFlags, void** pData)
	{
		return vkMapMemory(sDevice->GetDevice(), pMemory, pOffset, pSize, pMapFlags, pData);
	}

	void Objects::UnMapMemory(const VkDeviceMemory pMemory)
	{
		vkUnmapMemory(sDevice->GetDevice(), pMemory);
	}

	VkResult Objects::AllocateDirectTransferCommand(VkCommandBuffer* pCommandBuffer)
	{
		VkCommandBufferAllocateInfo bufferInfo{VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
		bufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		bufferInfo.commandPool = sCommands->GetTransferCommandPool();
		bufferInfo.commandBufferCount = 1;

		return vkAllocateCommandBuffers(sDevice->GetDevice(), &bufferInfo, pCommandBuffer);
	}

	void Objects::SubmitAndFreeDirectTransferCommand(const VkCommandBuffer pCommandBuffer)
	{
		VkSubmitInfo submitInfo = {VK_STRUCTURE_TYPE_SUBMIT_INFO};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &pCommandBuffer;

		VK_VERIFY(vkQueueSubmit(sDevice->GetTransferQueue(), 1, &submitInfo, nullptr));
		VK_VERIFY(vkQueueWaitIdle(sDevice->GetTransferQueue()));

		vkFreeCommandBuffers(sDevice->GetDevice(), sCommands->GetTransferCommandPool(), 1, &pCommandBuffer);
	}

	VkResult Objects::CreateShaderModule(const VkShaderModuleCreateInfo& pCreateInfo, VkShaderModule* pModule)
	{
		return vkCreateShaderModule(sDevice->GetDevice(), &pCreateInfo, nullptr, pModule);
	}

	void Objects::DestroyShaderModule(const VkShaderModule pModule)
	{
		vkDestroyShaderModule(sDevice->GetDevice(), pModule, nullptr);
	}

}