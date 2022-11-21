#pragma once

#include "Cader/Types/Common.h"

namespace CDR {

	namespace Random
	{
		i16 Int16();
		i16 Int16(i16 pMin, i16 pMax);

		i32 Int32();
		i32 Int32(i32 pMin, i32 pMax);

		u16 UInt16();
		u16 UInt16(u16 pMin, u16 pMax);

		u32 UInt32();
		u32 UInt32(u32 pMin, u32 pMax);

		float Float();
		float Float(float pMin, float pMax);
	};

}