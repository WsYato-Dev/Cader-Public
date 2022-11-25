#include "Cader/Maths/Random.h"

#include <random>

namespace CDR::Random {

	static std::random_device sRandomDevice;
	static std::mt19937 sMt{sRandomDevice()};

	i16 Int16()
	{
		return std::uniform_int_distribution<i16>()(sMt);
	}

	i16 Int16(const i16 pMin, const i16 pMax)
	{
		return std::uniform_int_distribution<i16>(pMin, pMax)(sMt);
	}

	i32 Int32()
	{
		return std::uniform_int_distribution<i32>()(sMt);
	}

	i32 Int32(const i32 pMin, const i32 pMax)
	{
		return std::uniform_int_distribution<i32>(pMin, pMax)(sMt);
	}

	u16 UInt16()
	{
		return std::uniform_int_distribution<u16>()(sMt);
	}

	u16 UInt16(const u16 pMin, const u16 pMax)
	{
		return std::uniform_int_distribution<u16>(pMin, pMax)(sMt);
	}

	u32 UInt32()
	{
		return std::uniform_int_distribution<u32>()(sMt);
	}

	u32 UInt32(const u32 pMin, const u32 pMax)
	{
		return std::uniform_int_distribution<u32>(pMin, pMax)(sMt);
	}

	float Float()
	{
		return std::uniform_real_distribution<float>()(sMt);
	}

	float Float(const float pMin, const float pMax)
	{
		return std::uniform_real_distribution<float>(pMin, pMax)(sMt);
	}

}