#pragma once

#include "Cader/Utility/Assert.h"
#include "Cader/Utility/Random.h"
#include "Cader/Types/Common.h"

namespace CDR {

	struct Color final
	{
		constexpr Color() = default;

		explicit constexpr Color(float pValue)
			: r{pValue}
			, g{pValue}
			, b{pValue}
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

		constexpr float operator[](u8 pIndex) const
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

		constexpr float& operator[](u8 pIndex)
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

		static constexpr Color Lerp(const Color& pLhs, const Color& pRhs, float pT)
		{
			return Color(
				pLhs.r + pT * (pRhs.r - pLhs.r),
				pLhs.g + pT * (pRhs.g - pLhs.g),
				pLhs.b + pT * (pRhs.b - pLhs.b)
			);
		}

		static constexpr Color Hex(u32 pHex)
		{
			return Color(
				((pHex >> 24) & 0xFF) / 255.0f,
				((pHex >> 16) & 0xFF) / 255.0f,
				((pHex >> 8) & 0xFF) / 255.0f,
				(pHex & 0xFF) / 255.0f
			);
		}

		static Color Random()
		{
			return Color(
				Random::Float(0.0f, 1.0f),
				Random::Float(0.0f, 1.0f),
				Random::Float(0.0f, 1.0f)
			);
		}

		float r{1.0f};
		float g{1.0f};
		float b{1.0f};
		float a{1.0f};
	};

	namespace ColorList {

		constexpr Color White			/**/{1.0f};
		constexpr Color Gray			/**/{0.5f};
		constexpr Color Black			/**/{0.0f};

		constexpr Color Red				/**/{1.0f, 0.0f, 0.0f};
		constexpr Color Green			/**/{0.0f, 1.0f, 0.0f};
		constexpr Color Blue			/**/{0.0f, 0.0f, 1.0f};

		constexpr Color Yellow			/**/{1.0f, 1.0f, 0.0f};
		constexpr Color Magenta			/**/{1.0f, 0.0f, 1.0f};
		constexpr Color Cyan			/**/{0.0f, 1.0f, 1.0f};

	}

}