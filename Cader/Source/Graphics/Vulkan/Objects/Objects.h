#pragma once

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;

	namespace VK {

		class Device;

		class Objects final
		{
			friend Graphics;

			static const Device* sDevice;

			static void Init(const Device* pDevice);

		public:
			static VkResult CreateShaderModule(const VkShaderModuleCreateInfo& pCreateInfo, VkShaderModule* pModule);
			static void DestroyShaderModule(const VkShaderModule pModule);
		};

	}

}