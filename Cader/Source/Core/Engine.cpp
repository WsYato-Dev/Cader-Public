#include "Cader/Core/Engine.h"

#include "Cader/Core/Project.h"
#include "Cader/Core/StartupSettings.h"
#include "Cader/Core/Time.h"
#include "Cader/Types/Common.h"
#include "Cader/Window/Window.h"

namespace CDR {

	Engine::Engine()
	{
		sEngine = this;

		StartupSettings startupSettings;
		Project::Setup(mProjectSettings, startupSettings);

		mWindow = new Window(mEventSystem, mProjectSettings.title, startupSettings);

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
				HandleEvents();
			}
			else
			{
				mWindow->PollEvents();
				HandleEvents();

				Time::Update();
				Project::Update();
			}
		}
	}

	void Engine::HandleEvents()
	{
		if(mEventSystem.IsEmpty())
			return;

		for(u8 i = 0; i < mEventSystem.Count(); i++)
		{
			const Event e = mEventSystem.GetEvent(i);

			switch(e.type)
			{
				case EEventType::WindowClose: Quit(); break;
				case EEventType::WindowMinimize: break;
				case EEventType::WindowFocus: break;
				case EEventType::WindowResize: break;
				default: break;
			}
		}

		mEventSystem.Release();
	}

	void Engine::Quit()
	{
		mRunning = false;
	}

}