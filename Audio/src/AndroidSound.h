#pragma once 
#ifdef __ANDROID__
	#include "Java.h"
#endif 
#include <string>


namespace sb 
{
	// Warning: This class is deprecated
	// Android sound playback. Unfortunately, Wav playback seems not to function properly on Android Emulator with Api >= 21 
	// so better use the SDL implementation in Sound.h
	class AndroidSound
	{
	public:
		void load(std::string assetPath);

		void play();

	private: 
		#ifdef __ANDROID__
			jint m_id;
		#endif

		std::string m_assetPath;
	};
}