#pragma once

#include "Cader/Types/Common.h"

#include <array>

#include <vulkan/vulkan.h>

namespace CDR::VK {

	class StorageBuffer;

	class Default2D final
	{
	public:
		Default2D(u32 pSize);
		~Default2D();

		void Bind(const VkCommandBuffer pCommandBuffer);

		StorageBuffer& GetStorageBuffer() const noexcept { return *mStorageBuffer; }

	private:
		void InitPipelineLayout();
		void InitPipeline();
		void InitDescriptorInfo(u32 pSize);

	private:
		VkDescriptorSetLayout mDescriptorSetLayout;
		VkPipelineLayout mPipelineLayout;

		std::array<VkShaderModule, 2> mShaderModules;
		VkPipeline mPipeline;

		VkDescriptorPool mDescriptorPool;
		VkDescriptorSet mDescriptorSet;
		StorageBuffer* mStorageBuffer;
	};

}