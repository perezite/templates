#pragma once 
#include <SFML/Audio.hpp>
#include <string>

namespace sb 
{
	class MusicImpl
	{
	public:
		~MusicImpl();

		void load(std::string assetPath);

		void play();

		void stop();

		void setLooping(bool looping);

		void setVolume(float volume);

	private: 
		sf::Music m_music;

		std::string m_assetPath;
	};
}


