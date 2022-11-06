#pragma once

#include <vulkan/vulkan.h>

namespace CDR{

	class Graphics;
	class Window;

	namespace VK {

		class Instance final
		{
			friend Graphics;

			VkInstance mInstance = nullptr;
			VkSurfaceKHR mSurface = nullptr;

			Instance(Window* pWindow);
			~Instance();

			void InitInstance();
			void InitSurface(Window* pWindow);

		public:
			inline const VkInstance& GetInstance() const noexcept { return mInstance; }
			inline const VkSurfaceKHR& GetSurface() const noexcept { return mSurface; }
		};

	}

}