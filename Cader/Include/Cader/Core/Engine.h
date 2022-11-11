#pragma once

#include "Cader/Core/ProjectSettings.h"
#include "Cader/Window/EventSystem.h"

namespace CDR {

	int Main();

	class Graphics;
	class Input;
	class Window;

	class Engine final
	{
		friend int Main();

		static Engine* sEngine;

		ProjectSettings mProjectSettings{};
		EventSystem mEventSystem{};

		Window* mWindow{nullptr};
		Input* mInput{nullptr};

		Graphics* mGraphics{nullptr};

		bool mRunning{true};

		Engine();
		~Engine();

		void Loop();
		void HandleEvents();

	public:
		void Quit();

		static inline Engine& Get() { return *sEngine; }

		inline const ProjectSettings& GetProjectSettings() const noexcept { return mProjectSettings; }

		inline Window& GetWindow() const noexcept { return *mWindow; }
		inline Graphics& GetGraphics() const noexcept { return *mGraphics; }
	};

}