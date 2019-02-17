#include "MusicImpl.h"

// Setting ITERATOR_DEBUG_LEVEL = 0 in debug mode isn't gonny fly with SFML-Audio, so issue a warning if this were the case
#if defined(_ITERATOR_DEBUG_LEVEL) && defined(_DEBUG)
	#if (_ITERATOR_DEBUG_LEVEL == 0)
		warning setting _ITERATOR_DEBUG_LEVEL = 0 in debug mode will probably cause problems with music playback
	#endif
#endif

namespace sb
{
	MusicImpl::~MusicImpl()
	{
	}

	void MusicImpl::load(std::string assetPath)
	{
		m_music.openFromFile(assetPath);
	}

	void MusicImpl::play()
	{
		if (m_music.getStatus() == sf::Music::Playing)
			return;

		m_music.play();
	}

	void MusicImpl::stop()
	{
		m_music.stop();
	}

	void MusicImpl::setLooping(bool looping)
	{
		m_music.setLoop(looping);
	}

	void MusicImpl::setVolume(float volume)
	{
		m_music.setVolume(volume * 100.0f);
	}
}
