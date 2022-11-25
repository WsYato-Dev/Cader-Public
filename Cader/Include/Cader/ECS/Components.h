#pragma once

#include "Cader/Maths/Color.h"

#include <glm/vec2.hpp>

namespace CDR {

	struct Position2DComponent final
	{
		glm::vec2 position;
	};

	struct Size2DComponent final
	{
		glm::vec2 size;
	};

	struct ColorComponent final
	{
		Color color;
	};

}