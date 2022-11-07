#include "Cader/Graphics/Graphics.h"

#include "Vulkan/Device.h"
#include "Vulkan/Instance.h"

namespace CDR {

	Graphics::Graphics(Window* pWindow)
	{
		mInstance = new VK::Instance(pWindow);
		mDevice = new VK::Device(*mInstance);
	}

	Graphics::~Graphics()
	{
		mDevice->WaitIdle();

		delete mDevice;
		delete mInstance;
	}

	void Graphics::OnWindowMinimize(Event pEvent)
	{}

	void Graphics::OnWindowResize(Event pEvent)
	{}

}