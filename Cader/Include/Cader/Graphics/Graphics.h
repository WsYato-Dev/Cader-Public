#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Window/Event.h"

namespace CDR {

	class Engine;
	class Window;

	namespace VK {

		class Commands;
		class Device;
		class Instance;
		class RenderPass;
		class SwapChain;
		class Sync;

	}

	class Graphics final
	{
		friend Engine;

		VK::Instance* mInstance = nullptr;
		VK::Device* mDevice = nullptr;
		VK::SwapChain* mSwapChain = nullptr;
		VK::RenderPass* mRenderPass = nullptr;
		VK::Sync* mSync = nullptr;
		VK::Commands* mCommands = nullptr;

		u32 mSwapChainImageIndex = 0;
		u8 mInFlightFrameIndex = 0;
		bool mCanRender = true;

		Graphics(const Window& pWindow);
		~Graphics();

		void NewFrame();
		void RenderFrame();

		void OnWindowMinimize(Event pEvent);
		void OnWindowResize(Event pEvent);
	};

}