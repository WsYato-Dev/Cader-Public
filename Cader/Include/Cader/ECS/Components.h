#pragma once

#include "Cader/Types/Color.h"

#include <glm/vec2.hpp>

namespace CDR::Components {

	struct Position2D final
	{
		constexpr Position2D() = default;

		constexpr Position2D(const glm::vec2& pPosition)
			: position{pPosition}
		{}

		glm::vec2 position{0.0f};
	};

	struct Size2D final
	{
		constexpr Size2D() = default;

		constexpr Size2D(const glm::vec2& pSize)
			: size{pSize}
		{}

		glm::vec2 size{1.0f};
	};

	struct RenderTarget2D final
	{
		constexpr RenderTarget2D() = default;

		constexpr RenderTarget2D(const Color& pColor)
			: color{pColor}
		{}

		Color color{1.0f};
	};

}