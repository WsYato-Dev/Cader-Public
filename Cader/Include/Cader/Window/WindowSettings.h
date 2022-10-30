#pragma once

#include "Cader/Types/Common.h"

namespace CDR {

	enum class EWindowMode: u8
	{
		Windowed = 0,
		Maximized,
		Fullscreen
	};

	struct WindowSize final
	{
		u16 width;
		u16 height;

		inline bool operator==(WindowSize pOther) const noexcept
		{
			return width == pOther.width && height == pOther.height;
		}
	};

	struct WindowAspectRatio final
	{
		u8 numerator;
		u8 denominator;
	};

}