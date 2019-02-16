#include "AndroidAudio.h"
#include "../Logger.h"
#ifdef __ANDROID__
	#include "Java.h"
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_mixer.h>
#endif 

namespace sb
{
	bool AndroidAudio::m_isInit = false;
	bool AndroidAudio::m_isValid = true;

	void AndroidAudio::init()
	{
		#ifdef __ANDROID__
			SB_ERROR_IF(m_isInit) << "AndroidAudio::init() can only be called once" << std::endl;

			// initialize android playback
			jint result = sb::Java::callStaticIntMethod("org/libsdl/app/Audio", "isInit", "()I");
			SB_WARNING_IF2(result == 0, true) << "android audio was not init. Make sure you called Audio.init(this) in the java android activity" << std::endl;
			SB_WARNING_IF2(result == -1, true) << "unable to initialize android audio" << std::endl;

			m_isValid = (result == 1);
			m_isInit = true;
		#endif
	}
}
