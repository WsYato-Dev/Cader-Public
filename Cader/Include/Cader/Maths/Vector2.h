#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Utility/Assert.h"

namespace CDR {

	template<typename _T>
	struct Vector2 final
	{
		static const Vector2 Zero;
		static const Vector2 One;

		static const Vector2 Right;
		static const Vector2 Up;

		_T x{0};
		_T y{0};

		constexpr Vector2() = default;

		explicit constexpr Vector2(_T pValue)
			: x{pValue}
			, y{pValue}
		{}

		constexpr Vector2(_T pX, _T pY)
			: x{pX}
			, y{pY}
		{}

		constexpr Vector2(const Vector2&) = default;
		constexpr Vector2(Vector2&&) noexcept = default;

		constexpr Vector2& operator=(const Vector2&) = default;
		constexpr Vector2& operator=(Vector2&&) noexcept = default;

		constexpr _T operator[](u8 pIndex) const
		{
			switch(pIndex)
			{
				case 0: return x;
				case 1: return y;
				default: CDR_ASSERT(false);
			}
		}

		constexpr _T& operator[](u8 pIndex)
		{
			switch(pIndex)
			{
				case 0: return x;
				case 1: return y;
				default: CDR_ASSERT(false);
			}
		}

		constexpr bool operator==(const Vector2& pOther) const noexcept
		{
			return x == pOther.x && y == pOther.y;
		}

		constexpr bool operator!=(const Vector2& pOther) const noexcept
		{
			return !operator==(pOther);
		}

		constexpr void operator+=(const Vector2& pOther)
		{
			x += pOther.x;
			y += pOther.y;
		}

		constexpr Vector2 operator+(const Vector2& pOther) const noexcept
		{
			return Vector2(
				x + pOther.x,
				y + pOther.y
			);
		}

		constexpr void operator-=(const Vector2& pOther)
		{
			x -= pOther.x;
			y -= pOther.y;
		}

		constexpr Vector2 operator-(const Vector2& pOther) const noexcept
		{
			return Vector2(
				x - pOther.x,
				y - pOther.y
			);
		}

		constexpr void operator*=(const Vector2& pOther)
		{
			x *= pOther.x;
			y *= pOther.y;
		}

		constexpr Vector2 operator*(const Vector2& pOther) const noexcept
		{
			return Vector2(
				x * pOther.x,
				y * pOther.y
			);
		}

		constexpr void operator/=(const Vector2& pOther)
		{
			x /= pOther.x;
			y /= pOther.y;
		}

		constexpr Vector2 operator/(const Vector2& pOther) const noexcept
		{
			return Vector2(
				x / pOther.x,
				y / pOther.y
			);
		}

		constexpr void Lerp(const Vector2& pOther, float pT)
		{
			x = x + pT * (pOther.x - x);
			y = y + pT * (pOther.y - y);
		}
	};

	template<typename _T>
	static constexpr Vector2<_T> Lerp(const Vector2<_T>& pLhs, const Vector2<_T>& pRhs, float pT)
	{
		return Vector2(
			pLhs.x + pT * (pRhs.x - pLhs.x),
			pLhs.y + pT * (pRhs.y - pLhs.y)
		);
	}

	using Vector2f = Vector2<float>;

}