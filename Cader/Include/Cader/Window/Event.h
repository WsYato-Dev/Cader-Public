#pragma once

#include "Cader/Types/Common.h"

namespace CDR {

	enum class EEventType: u8
	{
		None = 0,
		WindowClose, WindowMinimize, WindowFocus, WindowResize
	};

	struct Event final
	{
		EEventType type;

		union
		{
			bool minimized;
			bool focused;

			struct
			{
				u16 width;
				u16 height;
			} size;
		};

		Event() = default;
		
		Event(EEventType pType)
			: type(pType)
		{}
	};

}