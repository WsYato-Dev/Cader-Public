#pragma once

#include "Cader/Core/Asset.h"
#include "Cader/Core/AssetHandle.h"

#include <unordered_map>

namespace CDR {

	class Engine;

	class AssetsLibrary
	{
		friend Engine;

		static AssetsLibrary* sInstance;

	protected:
		std::unordered_map<u32, Asset*> mAssets;

	private:
		AssetsLibrary();

		void Clear();

	protected:
		static AssetHandle RegisterAsset(Asset* pAsset);
		static void DestroyAsset(AssetHandle pHandle);
	};

}