#pragma once

#include "Cader/Types/Common.h"

namespace CDR {

	enum class EAssetType: u8
	{
		None = 0
	};

	using AssetID = u32;

	struct AssetHandle final
	{
	private:
		AssetID mID{0};
		EAssetType mType{EAssetType::None};

	public:
		constexpr AssetHandle() = default;

		constexpr AssetHandle(AssetID pID, EAssetType pType)
			: mID{pID}
			, mType{pType}
		{}

		constexpr AssetID ID() const noexcept { return mID; }
		constexpr EAssetType Type() const noexcept { return mType; }
	};

}