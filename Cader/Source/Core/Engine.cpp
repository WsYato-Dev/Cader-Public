#include "Cader/Core/Engine.h"

#include "Cader/Core/Project.h"
#include "Cader/Core/StartupSettings.h"
#include "Cader/Core/Time.h"
#include "Cader/Window/Window.h"

namespace CDR {

	Engine::Engine()
	{
		sEngine = this;

		StartupSettings startupSettings;
		Project::Setup(mProjectSettings, startupSettings);

		mWindow = new Window(mProjectSettings.title, startupSettings);

		Time::Init();
		Project::Init();

		mWindow->Show();
	}

	Engine::~Engine()
	{
		Project::PreCleanup();

		delete mWindow;

		Project::Cleanup();
	}

	void Engine::Loop()
	{
		while(mRunning)
		{
			if(!mWindow->IsFocused())
			{
				mWindow->WaitEvents();
			}
			else
			{
				Time::Update();

				mWindow->PollEvents();
				Project::Update();
			}
		}
	}

	void Engine::Quit()
	{
		mRunning = false;
	}

}