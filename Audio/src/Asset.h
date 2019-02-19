#pragma once

#include <string>

namespace sb 
{
	class Asset
	{
	public: 
		Asset(std::string assetPath) : m_assetPath(assetPath)
		{ }

		std::string getFilePath();

	protected:
		std::string getExecutablePath();

		std::string getExecutableFolderPath();

		std::string getAssetFolderPath();
	private:
		std::string m_assetPath;
	};
}