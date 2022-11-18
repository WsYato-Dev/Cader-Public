#pragma once

#include "Cader/Types/Common.h"
#include "Cader/Utility/Assert.h"

namespace CDR {

	template<typename _T>
	struct Vector3 final
	{
		static const Vector3 Zero;
		static const Vector3 One;

		static const Vector3 Right;
		static const Vector3 Up;
		static const Vector3 Forward;

		_T x{0};
		_T y{0};
		_T z{0};

		constexpr Vector3() = default;

		explicit constexpr Vector3(_T pValue)
			: x{pValue}
			, y{pValue}
			, z{pValue}
		{}

		constexpr Vector3(_T pX, _T pY, _T pZ)
			: x{pX}
			, y{pY}
			, z{pZ}
		{}

		constexpr Vector3(const Vector3&) = default;
		constexpr Vector3(Vector3&&) noexcept = default;

		constexpr Vector3& operator=(const Vector3&) = default;
		constexpr Vector3& operator=(Vector3&&) noexcept = default;

		constexpr _T operator[](u8 pIndex) const
		{
			switch(pIndex)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
				default: CDR_ASSERT(false);
			}
		}

		constexpr _T& operator[](u8 pIndex)
		{
			switch(pIndex)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
				default: CDR_ASSERT(false);
			}
		}

		constexpr bool operator==(const Vector3& pOther) const noexcept
		{
			return x == pOther.x && y == pOther.y && z == pOther.z;
		}

		constexpr bool operator!=(const Vector3& pOther) const noexcept
		{
			return !operator==(pOther);
		}

		constexpr void operator+=(const Vector3& pOther)
		{
			x += pOther.x;
			y += pOther.y;
			z += pOther.z;
		}

		constexpr Vector3 operator+(const Vector3& pOther) const noexcept
		{
			return Vector3(
				x + pOther.x,
				y + pOther.y,
				z + pOther.z
			);
		}

		constexpr void operator-=(const Vector3& pOther)
		{
			x -= pOther.x;
			y -= pOther.y;
			z -= pOther.z;
		}

		constexpr Vector3 operator-(const Vector3& pOther) const noexcept
		{
			return Vector3(
				x - pOther.x,
				y - pOther.y,
				z - pOther.z
			);
		}

		constexpr void operator*=(const Vector3& pOther)
		{
			x *= pOther.x;
			y *= pOther.y;
			z *= pOther.z;
		}

		constexpr Vector3 operator*(const Vector3& pOther) const noexcept
		{
			return Vector3(
				x * pOther.x,
				y * pOther.y,
				z * pOther.z
			);
		}

		constexpr void operator/=(const Vector3& pOther)
		{
			x /= pOther.x;
			y /= pOther.y;
			z /= pOther.z;
		}

		constexpr Vector3 operator/(const Vector3& pOther) const noexcept
		{
			return Vector3(
				x / pOther.x,
				y / pOther.y,
				z / pOther.z
			);
		}

		constexpr void Lerp(const Vector3& pOther, float pT)
		{
			x = x + pT * (pOther.x - x);
			y = y + pT * (pOther.y - y);
			z = z + pT * (pOther.z - z);
		}
	};

	template<typename _T>
	static constexpr Vector3<_T> Lerp(const Vector3<_T>& pLhs, const Vector3<_T>& pRhs, float pT)
	{
		return Vector3(
			pLhs.x + pT * (pRhs.x - pLhs.x),
			pLhs.y + pT * (pRhs.y - pLhs.y),
			pLhs.z + pT * (pRhs.z - pLhs.z)
		);
	}

	using Vector3f = Vector3<float>;

}