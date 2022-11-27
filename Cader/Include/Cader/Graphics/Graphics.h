#pragma once

#include "Cader/Core/PersistentSettings.h"
#include "Cader/Core/StartupSettings.h"
#include "Cader/Types/Color.h"
#include "Cader/Types/Common.h"
#include "Cader/Window/Event.h"

namespace CDR {

	class Engine;
	class Renderer2D;
	class Scene;
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
		Graphics(const Window& pWindow, const PersistentSettings& pPersistentSettings, const StartupSettings& pStartupSettings);
		~Graphics();

		void PrepareCleanup();

		void NewFrame();
		void RenderFrame(Scene& pScene);

		void OnWindowMinimize(const Event pEvent);
		void OnWindowResize(const Event pEvent);

	public:
		Color clearColor;

	private:
		VK::Instance* mInstance;
		VK::Device* mDevice;
		VK::SwapChain* mSwapChain;
		VK::RenderPass* mRenderPass;
		VK::Sync* mSync;
		VK::Commands* mCommands;

		Renderer2D* mRenderer2D;

		u32 mSwapChainImageIndex{0};
		u8 mInFlightFrameIndex{0};
		bool mCanRender{true};

		friend Engine;
	};

}