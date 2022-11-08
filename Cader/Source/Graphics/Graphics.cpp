#include "Cader/Graphics/Graphics.h"

#include "Cader/Core/Engine.h"
#include "Cader/Window/Window.h"
#include "Cader/Window/WindowSettings.h"

#include "Vulkan/Device.h"
#include "Vulkan/Instance.h"
#include "Vulkan/SwapChain.h"

namespace CDR {

	Graphics::Graphics(const Window& pWindow)
	{
		mInstance = new VK::Instance(pWindow);
		mDevice = new VK::Device(*mInstance);
		mSwapChain = new VK::SwapChain(*mInstance, *mDevice);
	}

	Graphics::~Graphics()
	{
		mDevice->WaitIdle();

		delete mSwapChain;
		delete mDevice;
		delete mInstance;
	}

	void Graphics::OnWindowMinimize(Event pEvent)
	{
		if(pEvent.windowMinimized)
		{
			mDevice->WaitIdle();
			mSwapChain->DestroySwapChain();
		}
		else
		{
			WindowSize size = Engine::Get().GetWindow()->GetSize();
			mSwapChain->CreateSwapChain(size.width, size.height);
		}
	}

	void Graphics::OnWindowResize(Event pEvent)
	{
		mDevice->WaitIdle();
		mSwapChain->DestroySwapChain();
		mSwapChain->CreateSwapChain(pEvent.windowSize.width, pEvent.windowSize.height);
	}

}