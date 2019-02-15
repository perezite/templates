#include "Music.h"
#include "AndroidAudio.h"
#include "Logger.h"
#include <SDL2/SDL.h>

namespace sb
{
	Music::~Music()
	{
		#ifdef __ANDROID__
			jint result = sb::Java::callStaticIntMethod("org/libsdl/app/Music", "release", "(I)I", m_id);
			SB_WARNING_IF2(result == jint(-1), true) << "unable to release music track " << m_assetPath << std::endl;
		#endif		
	}

	void Music::load(std::string assetPath)
	{
		#ifdef __ANDROID__
			if (!AndroidAudio::isInit()) AndroidAudio::init();
			if (!AndroidAudio::isValid()) return;

			m_assetPath = assetPath;
			validateFileEnding(assetPath);

			m_id = sb::Java::callStaticIntMethod("org/libsdl/app/Music", "loadAsync", "(Ljava/lang/String;)I", sb::Java::newUtfString(assetPath));
			SB_WARNING_IF2(m_id == jint(-1), true) << "unable to load music track " << assetPath << std::endl;
			
			jint loadResult = 0;
			while (loadResult == jint(0)) {
				loadResult = sb::Java::callStaticIntMethod("org/libsdl/app/Music", "isLoadComplete", "(I)I", m_id);
				SDL_Delay(1);
			}

			SB_WARNING_IF2(m_id == jint(-1), true) << "unable to complete loading of music track " << assetPath << std::endl;
		#endif
	}

	void Music::play()
	{
		#ifdef __ANDROID__
			if (!AndroidAudio::isValid()) return;

			jint result = sb::Java::callStaticIntMethod("org/libsdl/app/Music", "play", "(I)I", m_id);
			SB_WARNING_IF2(result == jint(-1), true) << "unable to play music track " << m_assetPath << std::endl;
		#endif
	}

	void Music::stop()
	{
		#ifdef __ANDROID__
			if (!AndroidAudio::isValid()) return;

			jint result = sb::Java::callStaticIntMethod("org/libsdl/app/Music", "stop", "(I)I", m_id);
			SB_WARNING_IF2(result == jint(-1), true) << "unable to stop music track " << m_assetPath << std::endl;
		#endif
	}

	void Music::setLooping(bool looping)
	{
		#ifdef __ANDROID__
			if (!AndroidAudio::isValid()) return;

			jint result = sb::Java::callStaticIntMethod("org/libsdl/app/Music", "setLooping", "(IZ)I", m_id, jboolean(looping));
			SB_WARNING_IF2(result == jint(-1), true) << "unable to set looping on music track " << m_assetPath << std::endl;
		#endif
	}

	void Music::setVolume(float volume)
	{
		#ifdef __ANDROID__
			if (!AndroidAudio::isValid()) return;

			jint result = sb::Java::callStaticIntMethod("org/libsdl/app/Music", "setVolume", "(IF)I", m_id, jfloat(volume));
			SB_WARNING_IF2(result == jint(-1), true) << "unable to set volume on music track " << m_assetPath << std::endl;
		#endif
	}

	void Music::validateFileEnding(std::string assetPath)
	{
		std::size_t pos = assetPath.rfind(".");    
		std::string ending = assetPath.substr(pos, std::string::npos);

		SB_ERROR_IF(ending != ".ogg") << "Music files must be in .ogg format" << std::endl;
	}
}
