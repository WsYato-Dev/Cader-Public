#pragma once

#include "Cader/Core/Engine.h"

namespace CDR {

	int Main()
	{
		{
			Engine engine;
			engine.Loop();
		}

		return 0;
	}

}