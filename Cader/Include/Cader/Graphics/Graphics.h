#pragma once

#include "Cader/Window/Event.h"

namespace CDR {

	class Engine;
	class Window;

	namespace VK {

		class Device;
		class Instance;
		class SwapChain;

	}

	class Graphics final
	{
		friend Engine;

		VK::Instance* mInstance = nullptr;
		VK::Device* mDevice = nullptr;
		VK::SwapChain* mSwapChain = nullptr;

		Graphics(const Window& pWindow);
		~Graphics();

		void OnWindowMinimize(Event pEvent);
		void OnWindowResize(Event pEvent);
	};

}