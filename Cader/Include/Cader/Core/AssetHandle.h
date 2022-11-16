#pragma once

#include "Cader/Types/Common.h"

namespace CDR {

	struct AssetHandle final
	{
	private:
		u32 mID{0};

	public:
		constexpr AssetHandle() = default;

		constexpr AssetHandle(u32 pID)
			: mID{pID}
		{}

		constexpr operator u32() const noexcept { return mID; }
	};

}