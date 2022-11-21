#include "PipelineHelper.h"

#include "Cader/Types/Common.h"

#include "../../Utility.h"
#include "../Objects.h"

namespace CDR::VK {

	void PipelineHelper::CreateShader(FilePath pPath, VkShaderModule* pModule)
	{
		File shaderFile;
		bool success = FileSystem::ReadFile(pPath, &shaderFile);

		if(!success)
			return;

		VkShaderModuleCreateInfo moduleInfo = {VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO};
		moduleInfo.codeSize = shaderFile.size();
		moduleInfo.pCode = (const u32*)&shaderFile[0];

		VK_VERIFY(Objects::CreateShaderModule(moduleInfo, pModule));
	}

}