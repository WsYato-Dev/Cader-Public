#include "Default2D.h"

#include "../../Utility.h"

#include "../Buffers.h"
#include "../Objects.h"

#include "PipelineHelper.h"

namespace CDR::VK {

	Default2D::Default2D(u32 pSize)
	{
		InitPipelineLayout();
		InitPipeline();
		InitDescriptorInfo(pSize);
	}

	Default2D::~Default2D()
	{
		delete mStorageBuffer;
		Objects::DestroyDescriptorPool(mDescriptorPool);
		Objects::DestroyPipeline(mPipeline);

		for(const auto& shaderModule : mShaderModules)
			Objects::DestroyShaderModule(shaderModule);

		Objects::DestroyPipelineLayout(mPipelineLayout);
		Objects::DestroyDescriptorSetLayout(mDescriptorSetLayout);
	}

	void Default2D::Bind(const VkCommandBuffer pCommandBuffer)
	{
		vkCmdBindPipeline(pCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, mPipeline);
		vkCmdBindDescriptorSets(pCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, mPipelineLayout, 0, 1, &mDescriptorSet, 0, nullptr);
	}

	void Default2D::InitPipelineLayout()
	{
		VkDescriptorSetLayoutBinding setLayoutBinding = {};
		setLayoutBinding.binding = 0;
		setLayoutBinding.descriptorCount = 1;
		setLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		setLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutCreateInfo setLayoutInfo = {VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO};
		setLayoutInfo.bindingCount = 1;
		setLayoutInfo.pBindings = &setLayoutBinding;

		VK_VERIFY(Objects::CreateDescriptorSetLayout(setLayoutInfo, &mDescriptorSetLayout));

		VkPipelineLayoutCreateInfo pipelineLayoutInfo = {VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.setLayoutCount = 1;
		pipelineLayoutInfo.pSetLayouts = &mDescriptorSetLayout;

		VK_VERIFY(Objects::CreatePipelineLayout(pipelineLayoutInfo, &mPipelineLayout));
	}

	void Default2D::InitPipeline()
	{
		PipelineHelper::CreateShader("Shaders/Compiled/Default2D.vert.spv", &mShaderModules[0]);
		PipelineHelper::CreateShader("Shaders/Compiled/Default2D.frag.spv", &mShaderModules[1]);

		std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages{};

		for(u8 i = 0; i < (u8)mShaderModules.size(); i++)
		{
			shaderStages[i].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStages[i].pName = "main";
			shaderStages[i].module = mShaderModules[i];
		}

		shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;

		constexpr std::array<VkDynamicState, 2> dynamicStates
		{
			VK_DYNAMIC_STATE_SCISSOR,
			VK_DYNAMIC_STATE_VIEWPORT
		};

		VkPipelineViewportStateCreateInfo viewportState = {VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO};
		viewportState.scissorCount = 0;
		viewportState.viewportCount = 0;

		VkPipelineDynamicStateCreateInfo dynamicState = {VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO};
		dynamicState.dynamicStateCount = (u32)dynamicStates.size();
		dynamicState.pDynamicStates = &dynamicStates[0];

		VkPipelineInputAssemblyStateCreateInfo inputAssemblyState = {VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
		inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		VkPipelineVertexInputStateCreateInfo vertexInputState = {VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
		vertexInputState.vertexAttributeDescriptionCount = 0;
		vertexInputState.vertexBindingDescriptionCount = 0;

		VkPipelineRasterizationStateCreateInfo rasterizationState = {VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};
		rasterizationState.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizationState.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizationState.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizationState.lineWidth = 1.0f;

		VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.blendEnable = false;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

		VkPipelineColorBlendStateCreateInfo colorBlendState = {VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
		colorBlendState.attachmentCount = 1;
		colorBlendState.pAttachments = &colorBlendAttachment;

		VkGraphicsPipelineCreateInfo pipelineInfo = {VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO};
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = &shaderStages[0];
		pipelineInfo.pDynamicState = &dynamicState;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pVertexInputState = &vertexInputState;
		pipelineInfo.pInputAssemblyState = &inputAssemblyState;
		pipelineInfo.pRasterizationState = &rasterizationState;
		pipelineInfo.pColorBlendState = &colorBlendState;
		pipelineInfo.layout = mPipelineLayout;

		VK_VERIFY(Objects::CreateGraphicsPipeline(&pipelineInfo, &mPipeline));
	}

	void Default2D::InitDescriptorInfo(u32 pSize)
	{
		VkDescriptorPoolSize poolSize = {};
		poolSize.descriptorCount = 1;
		poolSize.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

		VkDescriptorPoolCreateInfo poolInfo = {VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO};
		poolInfo.maxSets = 1;
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = &poolSize;

		VK_VERIFY(Objects::CreateDescriptorPool(poolInfo, &mDescriptorPool));

		mStorageBuffer = new StorageBuffer(pSize);

		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = mStorageBuffer->GetBuffer();
		bufferInfo.range = pSize;
		bufferInfo.offset = 0;

		VkDescriptorSetAllocateInfo descriptorSetInfo = {VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO};
		descriptorSetInfo.descriptorPool = mDescriptorPool;
		descriptorSetInfo.descriptorSetCount = 1;
		descriptorSetInfo.pSetLayouts = &mDescriptorSetLayout;

		VK_VERIFY(Objects::AllocateDescriptorSet(descriptorSetInfo, &mDescriptorSet));

		VkWriteDescriptorSet writeSet = {VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET};
		writeSet.dstBinding = 0;
		writeSet.dstSet = mDescriptorSet;
		writeSet.descriptorCount = 1;
		writeSet.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
		writeSet.pBufferInfo = &bufferInfo;

		Objects::UpdateDescriptorSet(1, &writeSet);
	}

}