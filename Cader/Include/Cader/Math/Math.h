#pragma once

#include <type_traits>

namespace CDR::Math {

	template<typename _T>
	constexpr _T Abs(_T pValue)
	{
		static_assert(std::is_integral_v<_T> || std::is_floating_point_v<_T>);
		return 0 < pValue ? pValue : -pValue;
	}

	template<typename _T>
	constexpr _T Min(const _T pA, const _T pB)
	{
		static_assert(std::is_integral_v<_T> || std::is_floating_point_v<_T>);
		return pA > pB ? pB : pA;
	}

	template<typename _T>
	constexpr _T Max(const _T pA, const _T pB)
	{
		static_assert(std::is_integral_v<_T> || std::is_floating_point_v<_T>);
		return pA > pB ? pA : pB;
	}

	template<typename _T>
	constexpr _T Lerp(const _T pA, const _T pB, float pT)
	{
		static_assert(std::is_integral_v<_T> || std::is_floating_point_v<_T>);
		return pA + pT * (pB - pA);
	}

}