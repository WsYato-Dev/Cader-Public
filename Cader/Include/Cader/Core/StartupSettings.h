#pragma once

#include "Cader/Maths/Color.h"
#include "Cader/Window/WindowSettings.h"

namespace CDR {

	struct StartupSettings final
	{
		Color windowClearColor{0.1f, 0.1f, 0.1f};
		WindowSize windowDefaultSize{1280, 720};
		WindowSize windowMinimumSize{400, 400};
		WindowAspectRatio windowAspectRatio{0, 0};
		EWindowMode windowMode{EWindowMode::Windowed};
		bool windowResizable{true};
		u8 startSceneIndex{0};
	};

}