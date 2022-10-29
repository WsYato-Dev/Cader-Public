#pragma once

#include "Cader/Core/Engine.h"

namespace CDR {

	static int Main()
	{
		{
			Engine engine;
			engine.Loop();
		}

		return 0;
	}

}