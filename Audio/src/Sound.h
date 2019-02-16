#pragma once 
#include <SDL2/SDL_mixer.h>
#include <string>

namespace sb 
{
	class Sound
	{
	public:
		static void init();
		
		~Sound();

		void load(std::string assetPath);

		void play();


	protected:
		void validateFileEnding(std::string assetPath);

	private:
		Mix_Chunk* m_sound;

		std::string m_assetPath;

		static bool m_isInit;

		static bool m_isValid;
	};
}