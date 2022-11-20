#pragma once

#include <vulkan/vulkan.h>

namespace CDR{

	class Graphics;
	class Window;

	namespace VK {

		class Instance final
		{
			friend Graphics;

			VkInstance mInstance;
			VkSurfaceKHR mSurface;

			Instance(const Window& pWindow);
			~Instance();

			void InitInstance();
			void InitSurface(const Window& pWindow);

		public:
			inline const VkInstance GetInstance() const noexcept { return mInstance; }
			inline const VkSurfaceKHR GetSurface() const noexcept { return mSurface; }
		};

	}

}