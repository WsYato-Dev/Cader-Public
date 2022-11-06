#include "Cader/Graphics/Graphics.h"

#include "Vulkan/Instance.h"

namespace CDR {

	Graphics::Graphics(Window* pWindow)
	{
		mInstance = new VK::Instance(pWindow);
	}

	Graphics::~Graphics()
	{
		delete mInstance;
	}

	void Graphics::OnWindowMinimize(Event pEvent)
	{}

	void Graphics::OnWindowResize(Event pEvent)
	{}

}