#pragma once

#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;
	class Window;

	namespace VK {

		class Instance final
		{
			Instance(const Window& pWindow);
			~Instance();

			void InitInstance();
			void InitSurface(const Window& pWindow);

		public:
			const VkInstance GetInstance() const noexcept { return mInstance; }
			const VkSurfaceKHR GetSurface() const noexcept { return mSurface; }

		private:
			VkInstance mInstance;
			VkSurfaceKHR mSurface;

			friend Graphics;
		};

	}

}