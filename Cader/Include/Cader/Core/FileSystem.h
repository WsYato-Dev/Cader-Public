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

		static constexpr u8 DirectoryMaxSize{128};

		static char sProgramDirectory[DirectoryMaxSize];
		static char sWorkingDirectory[DirectoryMaxSize];

		static void Init(FilePath pPath = nullptr);

	public:
		static inline FilePath GetProgramDirectory() { return sProgramDirectory; }
		static inline FilePath GetWorkingDirectory() { return sWorkingDirectory; }

		static void SetWorkingDirectory(FilePath pPath);

		static bool Exists(FilePath pPath);
		static bool ReadFile(FilePath pPath, File* pFile);
		static bool WriteFile(FilePath pPath, const std::string& pWrite);
	};

}