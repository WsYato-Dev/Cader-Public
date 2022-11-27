#pragma once

#include <type_traits>

namespace CDR::Math {

	template<typename _T>
	constexpr _T Abs(_T pValue)
	{
		static_assert(std::is_integral_v<_T> || std::is_floating_point_v<_T>);
		return pValue > (_T)0 ? pValue : -pValue;
	}

	template<typename _T>
	constexpr _T Min(_T pA, _T pB)
	{
		static_assert(std::is_integral_v<_T> || std::is_floating_point_v<_T>);
		return pA > pB ? pB : pA;
	}

	template<typename _T>
	constexpr _T Max(_T pA, _T pB)
	{
		static_assert(std::is_integral_v<_T> || std::is_floating_point_v<_T>);
		return pA > pB ? pA : pB;
	}

	template<typename _T>
	constexpr _T Lerp(_T pA, _T pB, float pT)
	{
		static_assert(std::is_integral_v<_T> || std::is_floating_point_v<_T>);
		return (_T)(pA + pT * (pB - pA));
	}

}