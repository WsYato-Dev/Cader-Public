#pragma once

#include "Cader/Types/Color.h"
#include "Cader/Window/WindowSettings.h"

namespace CDR {

	struct StartupSettings final
	{
		Color windowClearColor{0.1f, 0.1f, 0.1f};

		WindowSize windowDefaultSize{1280, 720};
		EWindowMode windowMode{EWindowMode::Windowed};

		u8 startSceneIndex{0};
	};

}