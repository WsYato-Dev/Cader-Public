#pragma once

#include "Cader/Window/WindowSettings.h"

namespace CDR {

	struct StartupSettings final
	{
		WindowSize windowDefaultSize = {1280, 720};
		WindowSize windowMinimumSize = {200, 200};
		WindowAspectRatio windowAspectRatio = {0, 0};
		EWindowMode windowMode = EWindowMode::Windowed;
		bool windowResizable = true;
	};

}