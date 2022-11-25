#include "Cader/Core/FileSystem.h"

#include "Cader/Utility/Assert.h"

#include <filesystem>
#include <fstream>

namespace CDR {

	char FileSystem::sProgramDirectory[DirectoryMaxSize];
	char FileSystem::sWorkingDirectory[DirectoryMaxSize];

	void FileSystem::Init(const FilePath pPath)
	{
		if(pPath)
			std::filesystem::current_path(pPath);

		const std::string currentPath = std::filesystem::current_path().string();
		CDR_ASSERT(currentPath.size() <= DirectoryMaxSize);

		for(u8 i = 0; i < (u8)currentPath.size(); i++)
			sProgramDirectory[i] = currentPath[i];

		for(u8 i = 0; i < (u8)currentPath.size(); i++)
			sWorkingDirectory[i] = sProgramDirectory[i];
	}

	void FileSystem::SetWorkingDirectory(const FilePath pPath)
	{
		CDR_ASSERT(pPath);
		std::filesystem::current_path(pPath);

		const std::string currentPath = std::filesystem::current_path().string();
		CDR_ASSERT(currentPath.size() <= DirectoryMaxSize - 1);

		for(u8 i = 0; i < (u8)currentPath.size(); i++)
			sWorkingDirectory[i] = currentPath[i];

		sWorkingDirectory[(u8)currentPath.size()] = 0;
	}

	bool FileSystem::Exists(const FilePath pPath)
	{
		return std::filesystem::exists(pPath);
	}

	bool FileSystem::ReadFile(const FilePath pPath, File* pFile)
	{
		CDR_ASSERT(pPath && pFile);

		if(pFile->size())
			pFile->clear();

		std::ifstream file(pPath, std::ios::binary | std::ios::ate);

		if(!file.is_open())
			return false;

		const u64 fileSize = file.tellg();
		CDR_ASSERT(fileSize);

		pFile->resize(fileSize);

		file.seekg(0);
		file.read(&(*pFile)[0], fileSize);

		file.close();
		CDR_ASSERT(!file.is_open());

		return true;
	}

	bool FileSystem::WriteFile(const FilePath pPath, const std::string& pWrite)
	{
		CDR_ASSERT(pPath && pWrite.size());

		std::ofstream file(pPath);

		if(!file.is_open())
			return false;

		file.write(pWrite.c_str(), pWrite.size());
		file.flush();

		file.close();
		CDR_ASSERT(!file.is_open());

		return true;
	}

}