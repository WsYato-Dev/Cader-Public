#pragma once

#include "Cader/Core/ProjectSettings.h"
#include "Cader/Core/StartupSettings.h"

namespace CDR {

	class Scene;

	namespace Project {

		extern void Setup(ProjectSettings* pProjectSettings, StartupSettings* pStartupSettings);
		extern void Init(Scene& pScene);
		extern void Update(Scene& pScene);
		extern void Cleanup(Scene& pScene);

	}

}