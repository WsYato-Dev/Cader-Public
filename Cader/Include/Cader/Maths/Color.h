#pragma once

#include "Cader/Maths/Random.h"
#include "Cader/Utility/Assert.h"
#include "Cader/Types/Common.h"

namespace CDR {

	struct Color final
	{
		constexpr Color() = default;

		explicit constexpr Color(const float pValue)
			: r{pValue}
			, g{pValue}
			, b{pValue}
		{}

		explicit constexpr Color(const u32 pHex)
			: r(((pHex >> 24) & 0xFF) / 255.0f)
			, g(((pHex >> 16) & 0xFF) / 255.0f)
			, b(((pHex >> 8) & 0xFF) / 255.0f)
			, a(((pHex) & 0xFF) / 255.0f)
		{}

		constexpr Color(const float pR, const float pG, const float pB)
			: r{pR}
			, g{pG}
			, b{pB}
		{}

		constexpr Color(const float pR, const float pG, const float pB, const float pA)
			: r{pR}
			, g{pG}
			, b{pB}
			, a{pA}
		{}

		constexpr Color(const Color&) = default;
		constexpr Color(Color&&) noexcept = default;

		constexpr Color& operator=(const Color&) = default;
		constexpr Color& operator=(Color&&) noexcept = default;

		constexpr float operator[](const u8 pIndex) const
		{
			switch(pIndex)
			{
				case 0: return r;
				case 1: return g;
				case 2: return b;
				case 3: return a;
				default: CDR_ASSERT(false);
			}
		}

		constexpr float& operator[](const u8 pIndex)
		{
			switch(pIndex)
			{
				case 0: return r;
				case 1: return g;
				case 2: return b;
				case 3: return a;
				default: CDR_ASSERT(false);
			}
		}

		constexpr bool operator==(const Color& pOther) const noexcept
		{
			return pOther.r == r && pOther.g == g && pOther.b == b && pOther.a == a;
		}

		constexpr bool operator!=(const Color& pOther) const noexcept
		{
			return !operator==(pOther);
		}

		constexpr void operator*=(const float pScaler)
		{
			r *= pScaler;
			g *= pScaler;
			b *= pScaler;
		}

		constexpr Color operator*(const float pScaler)
		{
			return Color(
				r * pScaler,
				g * pScaler,
				b * pScaler
			);
		}

		constexpr void operator*=(const Color& pColor)
		{
			r *= pColor.r;
			g *= pColor.g;
			b *= pColor.b;
		}

		constexpr Color operator*(const Color& pColor)
		{
			return Color(
				r * pColor.r,
				g * pColor.g,
				b * pColor.b
			);
		}

		constexpr void Lerp(const Color& pOther, const float pT)
		{
			r = r + pT * (pOther.r - r);
			g = g + pT * (pOther.g - g);
			b = b + pT * (pOther.b - b);
		}

		static constexpr Color Random()
		{
			return Color(
				Random::Float(0.0f, 1.0f),
				Random::Float(0.0f, 1.0f),
				Random::Float(0.0f, 1.0f)
			);
		}

		static constexpr Color RGB(const u8 pR, const u8 pG, const u8 pB)
		{
			return Color(
				(float)pR / 255.0f,
				(float)pG / 255.0f,
				(float)pB / 255.0f
			);
		}

		static constexpr Color RGBA(const u8 pR, const u8 pG, const u8 pB, const u8 pA)
		{
			return Color(
				(float)pR / 255.0f,
				(float)pG / 255.0f,
				(float)pB / 255.0f,
				(float)pA / 255.0f
			);
		}

		float r{1.0f};
		float g{1.0f};
		float b{1.0f};
		float a{1.0f};
	};

	static constexpr Color Lerp(const Color& pLhs, const Color& pRhs, const float pT)
	{
		return Color(
			pLhs.r + pT * (pRhs.r - pLhs.r),
			pLhs.g + pT * (pRhs.g - pLhs.g),
			pLhs.b + pT * (pRhs.b - pLhs.b)
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