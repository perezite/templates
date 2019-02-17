#include "Music.h"
#include "Logger.h"

#ifdef __ANDROID__
	#include "Android/MusicImpl.h"
#endif
#ifdef WIN32
	#include "Windows/MusicImpl.h"
#endif

namespace sb
{
	Music::Music()
	{
		m_musicImpl = new MusicImpl();
	}

	Music::~Music()
	{
		delete m_musicImpl;
	}

	void Music::load(std::string assetPath)
	{
		validateFileEnding(assetPath);
		m_musicImpl->load(assetPath);
	}

	void Music::play()
	{
		m_musicImpl->play();
	}

	void Music::stop()
	{
		m_musicImpl->stop();
	}

	void Music::setLooping(bool looping)
	{
		m_musicImpl->setLooping(looping);
	}

	void Music::setVolume(float volume)
	{
		volume = volume < 0 ? 0 : volume > 1 ? 1 : volume;

		m_musicImpl->setVolume(volume);
	}

	void Music::validateFileEnding(std::string assetPath)
	{
		std::size_t pos = assetPath.rfind(".");    
		std::string ending = assetPath.substr(pos, std::string::npos);

		SB_ERROR_IF(ending != ".ogg") << "Music files must be in .ogg format" << std::endl;
	}
}
