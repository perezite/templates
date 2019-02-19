#include "Asset.h"
#include "Logger.h"
#ifdef WIN32
	#include <windows.h>
#endif
#include <algorithm>

namespace sb
{
	std::string Asset::getFilePath()
	{
		return getAssetFolderPath() + '/' + m_assetPath;
	}

	std::string Asset::getExecutablePath()
	{
		#ifdef WIN32
			HMODULE hModule = GetModuleHandleW(NULL);
			WCHAR path[MAX_PATH];
			GetModuleFileNameW(hModule, path, MAX_PATH);
			std::wstring widePath(path);
			std::string narrowPath(widePath.begin(), widePath.end());
			return narrowPath;
		#elif defined( __ANDROID__)			
			sb::Logger().error() << "Android does not support this operation" << std::endl;
		#else
			#error The current platform does not support this function
		#endif

	}

	std::string Asset::getExecutableFolderPath()
	{
		#ifdef WIN32
			std::string executablePath = getExecutablePath();
			std::replace(executablePath.begin(), executablePath.end(), '\\', '/');
			std::size_t last = executablePath.rfind('/');
			executablePath = executablePath.substr(0, last);
			return executablePath;
		#elif defined(__ANDROID__)
			sb::Logger().error() << "Android does not support this operation" << std::endl;
		#else
			#error The current platform does not support this function
		#endif
	}

	std::string Asset::getAssetFolderPath() {
		#ifdef WIN32
			return getExecutableFolderPath() + "/../Assets";
		#elif defined(__ANDROID__)
			return "";
		#else
			#error The current platform does not support this function
		#endif

	}

}
