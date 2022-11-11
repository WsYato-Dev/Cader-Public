#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Window/InputInfo.h"

namespace CDR {

	enum class EEventType: u8
	{
		None = 0,
		WindowClose, WindowMinimize, WindowFocus, WindowResize,
		Key, MouseButton, MousePosition, MouseScroll
	};

	struct Event final
	{
		EEventType type;

		union
		{
			struct {} initializer{};

			bool windowMinimized;
			bool windowFocused;

			struct
			{
				u16 width;
				u16 height;
			} windowSize;

			Key key;
			MouseButton mouseButton;
			MousePosition mousePosition;
			i8 mouseScroll;
		};

		constexpr Event()
			: type{EEventType::None}
		{}

		explicit constexpr Event(EEventType pType)
			: type{pType}
		{}
	};

}