#include "Cader/Core/Engine.h"

#include "Cader/Core/Project.h"

namespace CDR {

	Engine::Engine()
	{
		sEngine = this;

		Project::Setup(mProjectSettings);
		Project::Init();
	}

	Engine::~Engine()
	{
		Project::PreCleanup();
		Project::Cleanup();
	}

	void Engine::Loop()
	{
		while(mRunning)
		{
			Project::Update();
		}
	}

	void Engine::Quit()
	{
		mRunning = false;
	}

}