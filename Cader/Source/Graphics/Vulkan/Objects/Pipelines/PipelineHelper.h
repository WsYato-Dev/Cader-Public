#pragma once

#include "Cader/Core/FileSystem.h"

#include <vulkan/vulkan.h>

namespace CDR::VK {

	namespace PipelineHelper {

		void CreateShader(const FilePath pPath, VkShaderModule* pModule);

	}

}