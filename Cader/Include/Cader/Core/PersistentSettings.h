#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Window/WindowSettings.h"

namespace CDR {

	struct PersistentSettings final
	{
		Text projectTitle{nullptr};

		WindowSize windowMinimumSize{400, 400};
		WindowAspectRatio windowAspectRatio{0, 0};
		bool windowResizable{true};

		u32 max2DQuads{1000};
	};

}