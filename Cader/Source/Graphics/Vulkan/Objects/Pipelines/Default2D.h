#pragma once

#include "Cader/Types/Common.h"

#include <vulkan/vulkan.h>

namespace CDR::VK {

	class StorageBuffer;

	class Default2D final
	{
		VkDescriptorSetLayout mDescriptorSetLayout;
		VkPipelineLayout mPipelineLayout;

		VkShaderModule mShaderModules[2];
		VkPipeline mPipeline;

		VkDescriptorPool mDescriptorPool;
		VkDescriptorSet mDescriptorSet;
		StorageBuffer* mStorageBuffer;

	public:
		Default2D(u32 pSize);
		~Default2D();

		void Bind(const VkCommandBuffer pCommandBuffer);

		inline StorageBuffer& GetStorageBuffer() const noexcept { return *mStorageBuffer; }

	private:
		void InitPipelineLayout();
		void InitPipeline();
		void InitDescriptorInfo(u32 pSize);
	};

}