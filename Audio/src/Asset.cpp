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
		std::string result;

		#ifdef WIN32
			result = getAssetFolderPath() + '/' + m_assetPath;
		#elif defined(__ANDROID__)
			result = m_assetPath;
		#else
			#error The current platform does not support this function		
		#endif

		return result;
	}

	std::string Asset::getExecutablePath()
	{
		std::string result;

		#ifdef WIN32
			HMODULE hModule = GetModuleHandleW(NULL);
			WCHAR path[MAX_PATH];
			GetModuleFileNameW(hModule, path, MAX_PATH);
			std::wstring widePath(path);
			std::string narrowPath(widePath.begin(), widePath.end());
			result = narrowPath;
		#elif defined( __ANDROID__)			
			sb::Logger().error() << "Android does not support this operation" << std::endl;
		#else
			#error The current platform does not support this function
		#endif

		return result;
	}

	std::string Asset::getExecutableFolderPath()
	{
		std::string result;

		#ifdef WIN32
			std::string executablePath = getExecutablePath();
			std::replace(executablePath.begin(), executablePath.end(), '\\', '/');
			std::size_t last = executablePath.rfind('/');
			executablePath = executablePath.substr(0, last);
			result = executablePath;
		#elif defined(__ANDROID__)
			sb::Logger().error() << "Android does not support this operation" << std::endl;
		#else
			#error The current platform does not support this function
		#endif

		return result;
	}

	std::string Asset::getAssetFolderPath() {
		std::string result;

		#ifdef WIN32
			result = getExecutableFolderPath() + "/../Assets";
		#elif defined(__ANDROID__)
			result = "";
		#else
			#error The current platform does not support this function
		#endif

		return result;
	}

}
