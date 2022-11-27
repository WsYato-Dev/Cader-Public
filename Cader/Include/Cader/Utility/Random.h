#pragma once

#include "Cader/Types/Common.h"

namespace CDR::Random {

	i16 Int16();
	i16 Int16(const i16 pMin, const i16 pMax);

	i32 Int32();
	i32 Int32(const i32 pMin, const i32 pMax);

	u16 UInt16();
	u16 UInt16(const u16 pMin, const u16 pMax);

	u32 UInt32();
	u32 UInt32(const u32 pMin, const u32 pMax);

	float Float();
	float Float(const float pMin, const float pMax);

}