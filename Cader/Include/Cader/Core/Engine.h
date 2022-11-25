#pragma once

#include "Cader/Core/ProjectSettings.h"

namespace CDR {

	int Main();

	class Graphics;
	class Scene;
	class Window;

	class Engine final
	{
		Engine();
		~Engine();

		void Loop();
		void HandleEvents();

	public:
		void Quit();

		void SetActiveScene(const u8 pSceneIndex);

		static Engine& Get() noexcept { return *sInstance; }

		Window& GetWindow() const noexcept { return *mWindow; }
		Graphics& GetGraphics() const noexcept { return *mGraphics; }
		Scene& GetActiveScene() const noexcept { return *mActiveScene; }

		const ProjectSettings& GetProjectSettings() const noexcept { return mProjectSettings; }

	private:
		static Engine* sInstance;

		Window* mWindow;
		Graphics* mGraphics;
		Scene* mActiveScene;

		ProjectSettings mProjectSettings;

		bool mRunning{true};

		friend int Main();
	};

}