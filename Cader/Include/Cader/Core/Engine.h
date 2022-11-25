#pragma once

#include "Cader/Core/ProjectSettings.h"
#include "Cader/Window/EventSystem.h"

namespace CDR {

	int Main();

	class Graphics;
	class Input;
	class Scene;
	class Window;

	class Engine final
	{
		friend int Main();

		static Engine* sInstance;

		ProjectSettings mProjectSettings;

		EventSystem mEventSystem;

		Window* mWindow;
		Input* mInput;

		Graphics* mGraphics;

		Scene* mActiveScene;

		bool mRunning{true};

		Engine();
		~Engine();

		void Loop();
		void HandleEvents();

	public:
		void Quit();

		static inline Engine& Get() { return *sInstance; }

		inline const ProjectSettings& GetProjectSettings() const noexcept { return mProjectSettings; }

		inline Window& GetWindow() const noexcept { return *mWindow; }
		inline Graphics& GetGraphics() const noexcept { return *mGraphics; }

		void SetActiveScene(u8 pSceneIndex);
		inline Scene& GetActiveScene() const noexcept { return *mActiveScene; }
	};

}