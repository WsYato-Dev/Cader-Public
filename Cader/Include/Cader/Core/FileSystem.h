#pragma once

#include "Cader/Types/Common.h"

#include <vector>
#include <string>

namespace CDR {

	using FilePath = Text;
	using File = std::vector<char>;

	class Engine;

	class FileSystem final
	{
		static void Init(const FilePath pPath = nullptr);

	public:
		static FilePath GetProgramDirectory() { return sProgramDirectory; }
		static FilePath GetWorkingDirectory() { return sWorkingDirectory; }

		static void SetWorkingDirectory(const FilePath pPath);

		static bool Exists(const FilePath pPath);
		static bool ReadFile(const FilePath pPath, File* pFile);
		static bool WriteFile(const FilePath pPath, const std::string& pWrite);

	private:
		static constexpr u8 DirectoryMaxSize{128};

		static char sProgramDirectory[DirectoryMaxSize];
		static char sWorkingDirectory[DirectoryMaxSize];

		friend Engine;
	};

}