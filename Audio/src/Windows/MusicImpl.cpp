#include "MusicImpl.h"

// make sure that nobody activated ITERATOR_DEBUG_LEVEL = 0 in debug mode. This isn't gonna fly with SFML-Audio
#if defined(_ITERATOR_DEBUG_LEVEL) && defined(_DEBUG)
	#if (_ITERATOR_DEBUG_LEVEL == 0)
		#error _ITERATOR_DEBUG_LEVEL = 0 cannot be set in debug mode because the SFML-Audio library is not compatible with that
	#endif
#endif

namespace sb
{
	MusicImpl::~MusicImpl()
	{
	}

	void MusicImpl::load(std::string assetPath)
	{
		m_music.openFromFile("orchestral.ogg");
	}

	void MusicImpl::play()
	{
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
		m_music.setVolume(volume);
	}
}
