#pragma once

#include "Cader/Types/Common.h"

// TODO: Create own containers
#include <vector>
#include <string>

namespace CDR {

	using FilePath = Text;
	using File = std::vector<char>;

	class Engine;

	class FileSystem final
	{
		friend Engine;

		static constexpr u8 WorkingDirectoryMaxSize{128};

		static char sWorkingDirectory[WorkingDirectoryMaxSize];

		static void Init();

	public:
		static inline FilePath GetWorkingDirectory() { return sWorkingDirectory; }
		static void SetWorkingDirectory(FilePath pPath);

		static void ReadFile(FilePath pPath, File* pFile);
		static void WriteFile(FilePath pPath, const std::string& pText);
	};

}