#include "Cader/Utility/Random.h"

#include <random>

namespace CDR::Random {

	static std::random_device sRandomDevice;
	static std::mt19937 sMt{sRandomDevice()};

	i16 Int16()
	{
		return std::uniform_int_distribution<i16>()(sMt);
	}

	i16 Int16(i16 pMin, i16 pMax)
	{
		return std::uniform_int_distribution<i16>(pMin, pMax)(sMt);
	}

	i32 Int32()
	{
		return std::uniform_int_distribution<i32>()(sMt);
	}

	i32 Int32(i32 pMin, i32 pMax)
	{
		return std::uniform_int_distribution<i32>(pMin, pMax)(sMt);
	}

	u16 UInt16()
	{
		return std::uniform_int_distribution<u16>()(sMt);
	}

	u16 UInt16(u16 pMin, u16 pMax)
	{
		return std::uniform_int_distribution<u16>(pMin, pMax)(sMt);
	}

	u32 UInt32()
	{
		return std::uniform_int_distribution<u32>()(sMt);
	}

	u32 UInt32(u32 pMin, u32 pMax)
	{
		return std::uniform_int_distribution<u32>(pMin, pMax)(sMt);
	}

	float Float()
	{
		return std::uniform_real_distribution<float>()(sMt);
	}

	float Float(float pMin, float pMax)
	{
		return std::uniform_real_distribution<float>(pMin, pMax)(sMt);
	}

}