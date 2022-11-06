#pragma once

#include "Cader/Window/Event.h"

namespace CDR {

	class Engine;
	class Window;

	namespace VK {

		class Instance;

	}

	class Graphics final
	{
		friend Engine;

		VK::Instance* mInstance = nullptr;

		Graphics(Window* pWindow);
		~Graphics();

		void OnWindowMinimize(Event pEvent);
		void OnWindowResize(Event pEvent);
	};

}