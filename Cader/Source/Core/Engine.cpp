#include "Cader/Core/Engine.h"

#include "Cader/Core/FileSystem.h"
#include "Cader/Core/Project.h"
#include "Cader/Core/StartupSettings.h"
#include "Cader/Core/Time.h"
#include "Cader/ECS/Scene.h"
#include "Cader/ECS/SceneManager.h"
#include "Cader/Graphics/Graphics.h"
#include "Cader/Types/Common.h"
#include "Cader/Utility/Assert.h"
#include "Cader/Window/EventSystem.h"
#include "Cader/Window/Input.h"
#include "Cader/Window/Window.h"

namespace CDR {

	Engine* Engine::sInstance;

	Engine::Engine()
	{
		CDR_ASSERT(!sInstance);
		sInstance = this;

		// TODO: Use a resource file instead of loading each resource individually
		Time::Init();
		FileSystem::Init("../../../../Cader/Resources/");

		StartupSettings startupSettings;
		Project::Setup(&mPersistentSettings, &startupSettings);

		mWindow = new Window(mPersistentSettings, startupSettings);
		mGraphics = new Graphics(*mWindow, mPersistentSettings, startupSettings);

		Input::Init(*mWindow);

		if(startupSettings.startSceneIndex)
		{
			SetActiveScene(startupSettings.startSceneIndex);
		}
		else
		{
			const u8 sceneIndex = SceneManager::Create("Default Scene");
			SetActiveScene(sceneIndex);
		}

		Project::Init(*mActiveScene);
	}

	Engine::~Engine()
	{
		mGraphics->PrepareCleanup();

		Project::Cleanup(*mActiveScene);

		SceneManager::DestroyAll();

		delete mGraphics;
		delete mWindow;
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

				mGraphics->NewFrame();

				Project::Update(*mActiveScene);

				mGraphics->RenderFrame(*mActiveScene);

				Time::Update();
				Input::Update();
			}
		}
	}

	void Engine::HandleEvents()
	{
		if(EventSystem::IsEmpty())
			return;

		for(u8 i = 0; i < EventSystem::Count(); i++)
		{
			const Event e = EventSystem::GetEvent(i);

			switch(e.type)
			{
				case EEventType::WindowClose:
				{
					Quit();
					break;
				}
				case EEventType::WindowMinimize:
				{
					if(!e.windowMinimized)
						Time::Recaliber();

					mGraphics->OnWindowMinimize(e);
					break;
				}
				case EEventType::WindowFocus:
				{
					if(e.windowFocused)
						Time::Recaliber();

					break;
				}
				case EEventType::WindowResize:
				{
					Time::Recaliber();
					mGraphics->OnWindowResize(e);
					break;
				}

				default: break;
			}
		}

		EventSystem::Release();
	}

	void Engine::Quit()
	{
		mRunning = false;
	}

	void Engine::SetActiveScene(u8 pSceneIndex)
	{
		mActiveScene = SceneManager::SetActiveScene(pSceneIndex);
	}

}