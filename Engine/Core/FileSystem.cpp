#include "FileSystem.h"
#include <filesystem>

namespace nc
{

	void nc::SetFilePath(const std::string& pathname)
	{
		std::filesystem::current_path(pathname);
	}

	std::string nc::GetFilePath()
	{
		return std::filesystem::current_path().string();
	}

}
