#include "Cader/Core/Engine.h"

namespace CDR {

	Engine::Engine()
	{
		sEngine = this;
	}

	Engine::~Engine()
	{}

	void Engine::Loop()
	{
		while(mRunning)
		{}
	}

	void Engine::Quit()
	{
		mRunning = false;
	}

}