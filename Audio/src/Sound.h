#pragma once 
#ifdef __ANDROID__
	#include <SDL2/SDL_mixer.h>
#endif
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
		#ifdef __ANDROID__
			Mix_Chunk* m_sound;
		#endif

		std::string m_assetPath;

		static bool m_isInit;

		static bool m_isValid;
	};
}