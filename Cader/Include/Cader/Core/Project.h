#pragma once

#include "Cader/Core/ProjectSettings.h"
#include "Cader/Core/StartupSettings.h"

namespace CDR::Project {

	extern void Setup(ProjectSettings& pSettings, StartupSettings& pStartupSettings);
	extern void Init();
	extern void Update();
	extern void PreCleanup();
	extern void Cleanup();

}