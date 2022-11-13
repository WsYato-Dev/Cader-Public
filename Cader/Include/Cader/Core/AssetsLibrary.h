#pragma once

#include "Cader/Core/AssetHandle.h"

#include <unordered_map>

namespace CDR {

	class AssetsLibrary;
	class Engine;

	class Asset
	{
		friend AssetsLibrary;

	protected:
		virtual ~Asset() = 0;
	};

	class AssetsLibrary
	{
		friend Engine;

		static AssetsLibrary* sInstance;

		std::unordered_map<AssetID, Asset*> mAssets;

		AssetsLibrary();

		void Clear();

	protected:
		static AssetID RegisterAsset(Asset* pAsset);
		static void DestroyAsset(AssetID pID);
	};

}