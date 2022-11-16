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

	AssetHandle AssetsLibrary::RegisterAsset(Asset* pAsset)
	{
		AssetHandle handle = Random::UInt32();

		while(sInstance->mAssets.find(handle) == sInstance->mAssets.end() || handle == 0)
			handle = Random::UInt32();

		sInstance->mAssets[handle] = pAsset;

		return handle;
	}

	void AssetsLibrary::DestroyAsset(AssetHandle pHandle)
	{
		assert(sInstance->mAssets.find(pHandle) != sInstance->mAssets.end());

		delete sInstance->mAssets[pHandle];
		sInstance->mAssets.erase(pHandle);
	}

}