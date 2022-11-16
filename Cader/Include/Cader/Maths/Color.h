#pragma once

#include "Cader/Maths/Random.h"
#include "Cader/Types/Common.h"

namespace CDR {

	struct Color final
	{
		float r{1.0f};
		float g{1.0f};
		float b{1.0f};
		float a{1.0f};

		constexpr Color() = default;

		explicit constexpr Color(float pValue)
			: r{pValue}
			, g{pValue}
			, b{pValue}
		{}

		explicit constexpr Color(u32 pHex)
			: r(((pHex >> 24) & 0xFF) / 255.0f)
			, g(((pHex >> 16) & 0xFF) / 255.0f)
			, b(((pHex >> 8) & 0xFF) / 255.0f)
			, a(((pHex) & 0xFF) / 255.0f)
		{}

		constexpr Color(float pR, float pG, float pB)
			: r{pR}
			, g{pG}
			, b{pB}
		{}

		constexpr Color(float pR, float pG, float pB, float pA)
			: r{pR}
			, g{pG}
			, b{pB}
			, a{pA}
		{}

		constexpr Color(const Color&) = default;
		constexpr Color(Color&&) noexcept = default;

		constexpr Color& operator=(const Color&) = default;
		constexpr Color& operator=(Color&&) noexcept = default;

		constexpr void operator*=(float pScaler)
		{
			r *= pScaler;
			g *= pScaler;
			b *= pScaler;
		}

		constexpr Color operator*(float pScaler)
		{
			return Color(r * pScaler, g * pScaler, b * pScaler);
		}

		constexpr void operator*=(const Color& pColor)
		{
			r *= pColor.r;
			g *= pColor.g;
			b *= pColor.b;
		}

		constexpr Color operator*(const Color& pColor)
		{
			return Color(r * pColor.r, g * pColor.g, b * pColor.b);
		}

		constexpr void Lerp(const Color& pColor, float pT)
		{
			r = r + pT * (pColor.r - r);
			g = g + pT * (pColor.g - g);
			b = b + pT * (pColor.b - b);
		}
	};

	static constexpr Color RGB2Color(u8 pR, u8 pG, u8 pB)
	{
		return Color(
			(float)pR / 255.0f,
			(float)pG / 255.0f,
			(float)pB / 255.0f
		);
	}

	static constexpr Color RGBA2Color(u8 pR, u8 pG, u8 pB, u8 pA)
	{
		return Color(
			(float)pR / 255.0f,
			(float)pG / 255.0f,
			(float)pB / 255.0f,
			(float)pA / 255.0f
		);
	}

	static constexpr Color LerpColor(const Color& pLhs, const Color& pRhs, float pT)
	{
		return Color(
			pLhs.r + pT * (pRhs.r - pLhs.r),
			pLhs.g + pT * (pRhs.g - pLhs.g),
			pLhs.b + pT * (pRhs.b - pLhs.b)
		);
	}

	static constexpr Color RandomColor()
	{
		return Color(
			Random::Float(0.0f, 1.0f),
			Random::Float(0.0f, 1.0f),
			Random::Float(0.0f, 1.0f)
		);
	}

	namespace ColorList {

		static constexpr Color White			/**/{1.0f};
		static constexpr Color Gray				/**/{0.5f};
		static constexpr Color Black			/**/{0.0f};

		static constexpr Color Red				/**/{1.0f, 0.0f, 0.0f};
		static constexpr Color Green			/**/{0.0f, 1.0f, 0.0f};
		static constexpr Color Blue				/**/{0.0f, 0.0f, 1.0f};

		static constexpr Color Yellow			/**/{1.0f, 1.0f, 0.0f};
		static constexpr Color Magenta			/**/{1.0f, 0.0f, 1.0f};
		static constexpr Color Cyan				/**/{0.0f, 1.0f, 1.0f};

	}

}