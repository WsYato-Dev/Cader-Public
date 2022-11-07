#pragma once

#include "Cader/Window/Event.h"

namespace CDR {

	class Engine;
	class Window;

	namespace VK {

		class Device;
		class Instance;

	}

	class Graphics final
	{
		friend Engine;

		VK::Instance* mInstance = nullptr;
		VK::Device* mDevice = nullptr;

		Graphics(Window* pWindow);
		~Graphics();

		void OnWindowMinimize(Event pEvent);
		void OnWindowResize(Event pEvent);
	};

}