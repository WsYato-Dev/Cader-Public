#include "Cader/Core/FileSystem.h"

#include "Cader/Utility/Assert.h"

#include <filesystem>
#include <fstream>

namespace CDR {

	char FileSystem::sWorkingDirectory[WorkingDirectoryMaxSize];

	void FileSystem::Init()
	{
		std::string currentPath = std::filesystem::current_path().string();
		CDR_ASSERT(currentPath.size() <= WorkingDirectoryMaxSize - 1);

		for(u8 i = 0; i < (u8)currentPath.size(); i++)
			sWorkingDirectory[i] = currentPath[i];

		sWorkingDirectory[(u8)currentPath.size()] = 0;
	}

	void FileSystem::SetWorkingDirectory(FilePath pPath)
	{
		CDR_ASSERT(pPath);
		std::filesystem::current_path(pPath);

		std::string currentPath = std::filesystem::current_path().string();
		CDR_ASSERT(currentPath.size() <= WorkingDirectoryMaxSize - 1);

		for(u8 i = 0; i < (u8)currentPath.size(); i++)
			sWorkingDirectory[i] = currentPath[i];

		sWorkingDirectory[(u8)currentPath.size()] = 0;
	}

	void FileSystem::ReadFile(FilePath pPath, File* pFile)
	{
		CDR_ASSERT(pPath && pFile);

		if(pFile->size())
			pFile->clear();

		std::ifstream file(pPath, std::ios::binary | std::ios::ate);
		CDR_ASSERT(file.is_open());

		const u64 fileSize = file.tellg();
		CDR_ASSERT(fileSize);

		pFile->resize(fileSize + 1);

		file.seekg(0);
		file.read(&(*pFile)[0], fileSize);

		file.close();
		CDR_ASSERT(!file.is_open());
	}

	void FileSystem::WriteFile(FilePath pPath, const std::string& pText)
	{
		CDR_ASSERT(pPath && pText.size());

		std::ofstream file(pPath);
		CDR_ASSERT(file.is_open());

		file.write(pText.c_str(), pText.size());
		file.flush();

		file.close();
		CDR_ASSERT(!file.is_open());
	}

}