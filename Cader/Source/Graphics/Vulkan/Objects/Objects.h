#pragma once

#include "Cader/Types/Common.h"

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;

	namespace VK {

		class Commands;
		class Device;
		class RenderPass;

		class Objects final
		{
			friend Graphics;

			static const Device* sDevice;
			static const Commands* sCommands;
			static const RenderPass* sRenderPass;

			static void Init(const Device* pDevice, const Commands* pCommands, const RenderPass* pRenderPass);

		public:
			// Buffer
			static VkResult CreateBuffer(const VkBufferCreateInfo& pCreateInfo, VkBuffer* pBuffer);
			static void DestroyBuffer(const VkBuffer pBuffer);

			static void GetBufferMemoryRequirements(const VkBuffer pBuffer, VkMemoryRequirements* pMemoryRequirements);
			static VkResult BindBufferMemory(const VkBuffer pBuffer, const VkDeviceMemory pMemory);

			// Memory
			static u32 FindMemoryType(u32 pFilter, VkMemoryPropertyFlags pMemoryProperties);

			static VkResult AllocateMemory(const VkMemoryAllocateInfo& pAllocateInfo, VkDeviceMemory* pMemory);
			static void FreeMemory(const VkDeviceMemory pMemory);

			static VkResult MapMemory(const VkDeviceMemory pMemory, u32 pOffset, u32 pSize, VkMemoryMapFlags pMapFlags, void** pData);
			static void UnMapMemory(const VkDeviceMemory pMemory);

			// Direct Transfer Command
			static VkResult AllocateDirectTransferCommand(VkCommandBuffer* pCommandBuffer);
			static void SubmitAndFreeDirectTransferCommand(const VkCommandBuffer pCommandBuffer);

			// Shader Module
			static VkResult CreateShaderModule(const VkShaderModuleCreateInfo& pCreateInfo, VkShaderModule* pModule);
			static void DestroyShaderModule(const VkShaderModule pModule);

			// Pipeline Layout
			static VkResult CreatePipelineLayout(const VkPipelineLayoutCreateInfo& pCreateInfo, VkPipelineLayout* pLayout);
			static void DestroyPipelineLayout(const VkPipelineLayout pLayout);

			// Graphics Pipeline
			static VkResult CreateGraphicsPipeline(VkGraphicsPipelineCreateInfo& pCreateInfo, VkPipeline* pPipeline);
			static void DestroyPipeline(const VkPipeline pPipeline);
		};

	}

}