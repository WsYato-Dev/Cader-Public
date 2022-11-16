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
		virtual ~Asset() = default;
	};

	class AssetsLibrary
	{
		friend Engine;

		static AssetsLibrary* sInstance;

	protected:
		std::unordered_map<AssetHandle, Asset*> mAssets;

	private:
		AssetsLibrary();

		void Clear();

	protected:
		static AssetHandle RegisterAsset(Asset* pAsset);
		static void DestroyAsset(AssetHandle pHandle);
	};

}