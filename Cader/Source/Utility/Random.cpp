#include "Cader/Utility/Random.h"

#include <random>

namespace CDR {

	static std::random_device sRandomDevice;
	static std::mt19937 sMt(sRandomDevice());

	i16 Random::Int16()
	{
		return std::uniform_int_distribution<i16>()(sMt);
	}

	i32 Random::Int32()
	{
		return std::uniform_int_distribution<i32>()(sMt);
	}

	i64 Random::Int64()
	{
		return std::uniform_int_distribution<i64>()(sMt);
	}

	u16 Random::UInt16()
	{
		return std::uniform_int_distribution<u16>()(sMt);
	}

	u32 Random::UInt32()
	{
		return std::uniform_int_distribution<u32>()(sMt);
	}

	u64 Random::UInt64()
	{
		return std::uniform_int_distribution<u64>()(sMt);
	}

	float Random::Float()
	{
		return std::uniform_real_distribution<float>()(sMt);
	}

}