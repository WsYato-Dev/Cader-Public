#pragma once

#include "Cader/Types/Color.h"
#include "Cader/Window/WindowSettings.h"

namespace CDR {

	struct StartupSettings final
	{
		Color windowClearColor{0.5f, 0.8f, 1.0f};
		WindowSize windowDefaultSize{1280, 720};
		WindowSize windowMinimumSize{200, 200};
		WindowAspectRatio windowAspectRatio{0, 0};
		EWindowMode windowMode{EWindowMode::Windowed};
		bool windowResizable{true};
	};

}