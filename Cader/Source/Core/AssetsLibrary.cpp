#include "Cader/Core/AssetsLibrary.h"

#include "Cader/Utility/Random.h"

#include <assert.h>

namespace CDR {

	AssetsLibrary* AssetsLibrary::sInstance{nullptr};

	AssetsLibrary::AssetsLibrary()
	{
		assert(!sInstance);
		sInstance = this;
	}

	void AssetsLibrary::Clear()
	{
		for(const auto& asset : mAssets)
			delete asset.second;

		mAssets.clear();
	}

	AssetID AssetsLibrary::RegisterAsset(Asset* pAsset)
	{
		AssetID id = Random::UInt32();

		while(sInstance->mAssets.find(id) == sInstance->mAssets.end() || id == 0)
			id = Random::UInt32();

		sInstance->mAssets[id] = pAsset;

		return id;
	}

	void AssetsLibrary::DestroyAsset(AssetID pID)
	{
		assert(sInstance->mAssets.find(pID) != sInstance->mAssets.end());

		delete sInstance->mAssets[pID];
		sInstance->mAssets.erase(pID);
	}

}