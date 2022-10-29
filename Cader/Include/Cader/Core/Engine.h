#pragma once

#include "Cader/Core/ProjectSettings.h"

namespace CDR {

	int Main();

	class Engine final
	{
		friend int Main();

		static inline Engine* sEngine;

		ProjectSettings mProjectSettings;
		bool mRunning = true;

		Engine();
		~Engine();

		void Loop();

	public:
		static inline Engine& Get() { return *sEngine; }

		void Quit();
	};

}