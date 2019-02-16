#pragma once 
#include <string>

namespace sb 
{
	class MusicImpl;

	class Music
	{
	public:
		Music();

		~Music();

		void load(std::string assetPath);

		void play();

		void stop();

		void setLooping(bool looping);

		void setVolume(float volume);

	protected:
		void validateFileEnding(std::string assetPath);

	private: 
		MusicImpl* m_musicImpl;
	};
}


