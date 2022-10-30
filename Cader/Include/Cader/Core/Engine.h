#pragma once

#include "Cader/Core/ProjectSettings.h"

namespace CDR {

	int Main();

	class Window;

	class Engine final
	{
		friend int Main();

		static inline Engine* sEngine;

		ProjectSettings mProjectSettings;
		Window* mWindow = nullptr;

		bool mRunning = true;

		Engine();
		~Engine();

		void Loop();

	public:
		void Quit();

		static inline Engine& Get() { return *sEngine; }

		inline const ProjectSettings& GetProjectSettings() const noexcept { return mProjectSettings; }
		inline Window* GetWindow() const noexcept { return mWindow; }
	};

}