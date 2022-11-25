#pragma once

#include "Cader/Maths/Color.h"
#include "Cader/Types/Common.h"

#include "Vulkan/Objects/Buffers.h"
#include "Vulkan/Objects/Pipelines/Default2D.h"

#include <vector>

#include <glm/vec2.hpp>
#include <vulkan/vulkan.h>

namespace CDR {

	class Graphics;
	class Scene;

	struct alignas(32) RenderTarget final
	{
		Color color;
		glm::vec2 position;
		glm::vec2 size;
	};

	class Renderer2D final
	{
		Renderer2D(const u32 pMaxQuads);
		~Renderer2D();

		void Render(Scene& pScene, const VkCommandBuffer pCommandBuffer);

		std::vector<RenderTarget> mRenderTargets;

		VK::IndexBuffer* mIndexBuffer;
		VK::Default2D* mDefault2D;

		friend Graphics;
	};

}