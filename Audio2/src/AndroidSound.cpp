#include "AndroidSound.h"
#include "AndroidAudio.h"
#include "Logger.h"
#include <SDL2/SDL.h>

namespace sb
{
	void AndroidSound::load(std::string assetPath)
	{
		#ifdef __ANDROID__
			SB_WARNING() << "The AndroidSound class is deprecated, use the Sound class instead!" << std::endl;

			if (!AndroidAudio::isInit())
				AndroidAudio::init();

			m_assetPath = assetPath;

			m_id = sb::Java::callStaticIntMethod("org/libsdl/app/Sound", "loadAsync", "(Ljava/lang/String;)I", sb::Java::newUtfString(assetPath));
			SB_WARNING_IF2(m_id != jint(1), true) << "unable to load android sound " << assetPath << std::endl;

			jint result = jint(0);
			while (result == jint(0)) {
				result = sb::Java::callStaticIntMethod("org/libsdl/app/Sound", "isLoadComplete", "(I)I", m_id);
				SDL_Delay(1);
			}

			SB_WARNING_IF2(result != jint(1), true) << "unable to complete loading of android sound " << assetPath << std::endl;
		#endif
	}

	void AndroidSound::play()
	{
		#ifdef __ANDROID__
			jint result = sb::Java::callStaticIntMethod("org/libsdl/app/Sound", "play", "(I)I", m_id);
			SB_WARNING_IF2(result != jint(1), true) << "unable to play android sound " << m_assetPath << std::endl;
		#endif
	}
}
