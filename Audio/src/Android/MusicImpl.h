#pragma once 
#ifdef __ANDROID__
	#include "Java.h"
#endif 
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
		#ifdef __ANDROID__
			jint m_id;
		#endif

		std::string m_assetPath;
	};
}


