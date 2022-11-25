#include "Objects.h"

#include "../Commands.h"
#include "../Device.h"
#include "../RenderPass.h"
#include "../Utility.h"

namespace CDR::VK {

	const Device* Objects::sDevice;
	const Commands* Objects::sCommands;
	const RenderPass* Objects::sRenderPass;

	void Objects::Init(const Device* pDevice, const Commands* pCommands, const RenderPass* pRenderPass)
	{
		sDevice = pDevice;
		sCommands = pCommands;
		sRenderPass = pRenderPass;
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

	u32 Objects::FindMemoryType(const u32 pFilter, const VkMemoryPropertyFlags pMemoryProperties)
	{
		const VkPhysicalDeviceMemoryProperties& memoryProperties = sDevice->GetMemoryProperties();

		for(u32 i = 0; i < memoryProperties.memoryTypeCount; i++)
			if((pFilter & (1 << i)) && (pMemoryProperties & memoryProperties.memoryTypes[i].propertyFlags) == pMemoryProperties)
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

	VkResult Objects::MapMemory(const VkDeviceMemory pMemory, const u32 pOffset, const u32 pSize, VkMemoryMapFlags pMapFlags, void** pData)
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

	VkResult Objects::CreateDescriptorSetLayout(const VkDescriptorSetLayoutCreateInfo& pCreateInfo, VkDescriptorSetLayout* pSetLayout)
	{
		return vkCreateDescriptorSetLayout(sDevice->GetDevice(), &pCreateInfo, nullptr, pSetLayout);
	}

	void Objects::DestroyDescriptorSetLayout(const VkDescriptorSetLayout pSetLayout)
	{
		vkDestroyDescriptorSetLayout(sDevice->GetDevice(), pSetLayout, nullptr);
	}

	VkResult Objects::CreatePipelineLayout(const VkPipelineLayoutCreateInfo& pCreateInfo, VkPipelineLayout* pLayout)
	{
		return vkCreatePipelineLayout(sDevice->GetDevice(), &pCreateInfo, nullptr, pLayout);
	}

	void Objects::DestroyPipelineLayout(const VkPipelineLayout pLayout)
	{
		vkDestroyPipelineLayout(sDevice->GetDevice(), pLayout, nullptr);
	}

	VkResult Objects::CreateGraphicsPipeline(VkGraphicsPipelineCreateInfo* pCreateInfo, VkPipeline* pPipeline)
	{
		pCreateInfo->renderPass = sRenderPass->GetRenderPass();
		return vkCreateGraphicsPipelines(sDevice->GetDevice(), nullptr, 1, pCreateInfo, nullptr, pPipeline);
	}

	void Objects::DestroyPipeline(const VkPipeline pPipeline)
	{
		vkDestroyPipeline(sDevice->GetDevice(), pPipeline, nullptr);
	}

	VkResult Objects::CreateDescriptorPool(const VkDescriptorPoolCreateInfo& pCreateInfo, VkDescriptorPool* pDescriptorPool)
	{
		return vkCreateDescriptorPool(sDevice->GetDevice(), &pCreateInfo, nullptr, pDescriptorPool);
	}

	void Objects::DestroyDescriptorPool(const VkDescriptorPool pDescriptorPool)
	{
		vkDestroyDescriptorPool(sDevice->GetDevice(), pDescriptorPool, nullptr);
	}

	VkResult Objects::AllocateDescriptorSet(const VkDescriptorSetAllocateInfo& pAllocateInfo, VkDescriptorSet* pDescriptorSets)
	{
		return vkAllocateDescriptorSets(sDevice->GetDevice(), &pAllocateInfo, pDescriptorSets);
	}

	void Objects::UpdateDescriptorSet(const u8 pWritesCount, const VkWriteDescriptorSet* pWrites)
	{
		vkUpdateDescriptorSets(sDevice->GetDevice(), pWritesCount, pWrites, 0, nullptr);
	}

}