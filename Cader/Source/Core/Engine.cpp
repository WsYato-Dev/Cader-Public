#include "Cader/Core/Engine.h"

#include "Cader/Core/Project.h"
#include "Cader/Core/StartupSettings.h"
#include "Cader/Core/Time.h"
#include "Cader/Graphics/Graphics.h"
#include "Cader/Types/Common.h"
#include "Cader/Window/Input.h"
#include "Cader/Window/Window.h"

namespace CDR {

	Engine* Engine::sEngine = nullptr;

	Engine::Engine()
	{
		sEngine = this;

		StartupSettings startupSettings;
		Project::Setup(mProjectSettings, startupSettings);

		mWindow = new Window(mProjectSettings.title, startupSettings);
		mInput = new Input(*mWindow);

		mGraphics = new Graphics(*mWindow, startupSettings);

		Time::Init();
		Project::Init();

		mWindow->Show();
	}

	Engine::~Engine()
	{
		Project::PreCleanup();

		delete mGraphics;

		delete mInput;
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

				mGraphics->NewFrame();

				Project::Update();

				mGraphics->RenderFrame();

				mInput->Update();
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
				case EEventType::WindowMinimize: mGraphics->OnWindowMinimize(e); break;
				case EEventType::WindowResize: mGraphics->OnWindowResize(e); break;

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