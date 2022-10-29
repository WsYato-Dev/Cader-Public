#pragma once

#include "Cader/Core/ProjectSettings.h"

namespace CDR::Project {

	extern void Setup(ProjectSettings& pSettings);
	extern void Init();
	extern void Update();
	extern void PreCleanup();
	extern void Cleanup();

}