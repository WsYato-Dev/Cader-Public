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
		u16 width{0};
		u16 height{0};

		constexpr WindowSize() = default;

		constexpr WindowSize(u16 pWidth, u16 pHeight)
			: width{pWidth}
			, height{pHeight}
		{}

		inline bool operator==(WindowSize pOther) const noexcept
		{
			return width == pOther.width && height == pOther.height;
		}
	};

	struct WindowAspectRatio final
	{
		u8 numerator{0};
		u8 denominator{0};

		constexpr WindowAspectRatio() = default;

		constexpr WindowAspectRatio(u8 pNumerator, u8 pDenominator)
			: numerator{pNumerator}
			, denominator{pDenominator}
		{}
	};

}