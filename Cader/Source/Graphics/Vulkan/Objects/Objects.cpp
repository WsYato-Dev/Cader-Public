#include "Objects.h"

#include "../Device.h"

namespace CDR::VK {

	const Device* Objects::sDevice{nullptr};

	void Objects::Init(const Device* pDevice)
	{
		sDevice = pDevice;
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