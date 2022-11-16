#pragma once

#include "Cader/Types/Common.h"

namespace CDR {

	namespace Random
	{
		extern i16 Int16();
		extern i16 Int16(i16 pMin, i16 pMax);

		extern i32 Int32();
		extern i32 Int32(i32 pMin, i32 pMax);

		extern u16 UInt16();
		extern u16 UInt16(u16 pMin, u16 pMax);

		extern u32 UInt32();
		extern u32 UInt32(u32 pMin, u32 pMax);

		extern float Float();
		extern float Float(float pMin, float pMax);
	};

}