#pragma once

namespace CDR {

	class AssetsLibrary;

	class Asset
	{
		friend AssetsLibrary;

	protected:
		virtual ~Asset() = default;
	};

}