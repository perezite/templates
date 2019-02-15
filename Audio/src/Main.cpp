#include "Window.h"
#include "Input.h"
#include "Sound.h"
#include "Music.h"
#include "Stopwatch.h"
#include "Logger.h"
#ifdef __ANDROID__
	#include "Java.h"
#endif
#include <SDL2/SDL.h>
#ifdef __ANDROID__
	#include <SDL2/SDL_mixer.h>
#endif
#include <iostream>

enum class PlaybackState {
	TheBeginning,
	TowSoundsTwoFadingMusics,
	TwoFadingMusics,
	LoopingMusic,
	TwoMusicsTwoSounds,
	TwoMusics,
	TwoSounds,
	OneSoundOneMusic,
	OneMusic,
	OneSound,
	TheEnd
};

static int tapCounter = 0;

PlaybackState playbackState = PlaybackState::TheBeginning;
sb::Sound sound1;
sb::Sound sound2;
sb::Music music1;
sb::Music music2;
sb::Music music3;

void playback() {
	if (playbackState == PlaybackState::TheBeginning) {
		playbackState = PlaybackState::TowSoundsTwoFadingMusics;
	}
	if (playbackState == PlaybackState::TowSoundsTwoFadingMusics) {
		SDL_Log("TowSoundsTwoFadingMusics");
		static int counter6 = 0;
		music1.setVolume(0);
		music2.setVolume(1);
		music1.play();
		music2.play();
		sound1.play();
		SDL_Log("0.5 second delay...");
		SDL_Delay(500);
		SDL_Log("Done");
		sound2.play();
		counter6++;
		if (counter6 == 3)
			playbackState = PlaybackState::TwoFadingMusics;
	}
	if (playbackState == PlaybackState::TwoFadingMusics) {
		SDL_Log("TwoFadingMusics");
		static int counter5 = 0;
		music1.stop();
		music2.stop();
		music1.setVolume(0);
		music2.setVolume(1);
		music1.play();
		music2.play();
		counter5++;
		if (counter5 == 2)
			playbackState = PlaybackState::LoopingMusic;
	}
	else if (playbackState == PlaybackState::LoopingMusic) {
		SDL_Log("LoopingMusic");
		music1.stop();
		music2.stop();
		music1.setVolume(1);
		music2.setVolume(1);
		music3.play();
		playbackState = PlaybackState::TwoMusicsTwoSounds;
	}
	else if (playbackState == PlaybackState::TwoMusicsTwoSounds)
	{
		SDL_Log("TwoMusicsTwoSounds");
		static unsigned int counter4 = 0;
		if (counter4 == 0) 
			music3.stop();
		music1.play();
		music2.play();
		sound2.play();
		SDL_Log("0.5 second delay...");
		SDL_Delay(500);
		SDL_Log("Done");
		sound1.play();
		counter4++;
		if (counter4 == 3)
			playbackState = PlaybackState::TwoMusics;
	}
	else if (playbackState == PlaybackState::TwoMusics) {
		SDL_Log("TwoMusics");
		music2.stop();
		music1.stop();
		music2.play();
		music1.play();
		playbackState = PlaybackState::TwoSounds;
	}
	else if (playbackState == PlaybackState::TwoSounds) {
		SDL_Log("TwoSounds");
		static unsigned int counter3 = 0;
		music1.stop();
		music2.stop();
		sound2.play();
		SDL_Log("0.5 second delay...");
		SDL_Delay(500);
		SDL_Log("Done");
		sound1.play();
		counter3++;
		if (counter3 == 3)
			playbackState = PlaybackState::OneSoundOneMusic;
	}
	else if (playbackState == PlaybackState::OneSoundOneMusic) {
		SDL_Log("OneSoundOneMusic");
		static unsigned int counter2 = 0;
		music1.play();
		sound1.play();
		counter2++;
		if (counter2 == 3)
			playbackState = PlaybackState::OneMusic;
	}
	else if (playbackState == PlaybackState::OneMusic) {
		SDL_Log("OneMusic");
		music2.stop();
		music1.play();
		playbackState = PlaybackState::OneSound;
	}
	if (playbackState == PlaybackState::OneSound) {
		SDL_Log("OneSound");
		static unsigned int counter1 = 0;
		music1.stop();
		sound1.play();
		counter1++;
		if (counter1 == 3)
			playbackState = PlaybackState::TheEnd;
	}
	else if (playbackState == PlaybackState::TheEnd) {
		SDL_Log("The end");
		music1.stop();
	}
}

float clamp(float value, float min, float max)
{
	return value < min ? min : (value > max ? max : value);
}

void fadeMusic(sb::Music& music, sb::Stopwatch& sw, float& volume, bool& volumeIncreasing)
{
	volumeIncreasing = volume <= 0 ? true : volume >= 1 ? false : volumeIncreasing;
	volume = clamp(volume, 0, 1);
	float deltaVolume = sw.getElapsedSeconds() / 5;
	sw.reset();
	volume += volumeIncreasing ? deltaVolume : -deltaVolume;
	music.setVolume(volume);
}

void fadeMusics()

{
	static sb::Stopwatch music1Sw;
	static float volume1 = 0;
	static bool volume1Increasing = true;

	static sb::Stopwatch music2Sw;
	static float volume2 = 1;
	static bool volume2Increasing = false;

	fadeMusic(music1, music1Sw, volume1, volume1Increasing);
	fadeMusic(music2, music2Sw, volume2, volume2Increasing);
	SDL_Log("%f %f", volume1, volume2);
}

void updatePlayback()
{
	if (playbackState == PlaybackState::TowSoundsTwoFadingMusics || playbackState == PlaybackState::TwoFadingMusics) {
		fadeMusics();
	}
}

void update()
{
	if (sb::Input::isMouseGoingDown() || sb::Input::isTouchGoingDown()) {
		SDL_Log("tap");
		playback();
	}

	updatePlayback();
}

void init()
{
	sound1.load("ding.ogg");
	sound2.load("losing.wav");
	music1.load("ukulele.ogg");
	music2.load("idea.ogg");
	music3.load("losing.ogg");
	music3.setLooping(true);
}

void update2()
{
	if (sb::Input::isTouchGoingDown()) {
		SDL_Log("tap");
		music1.play();
		sound1.play();
		tapCounter++;
	}
}

void run() 
{
	sb::Window window;
	init();

	while (window.isOpen()) {
		/*if (tapCounter == 2)
			window.close();*/


		window.update();
		update();
		// update2();
		window.draw();
	}
}

int main(int argc, char* args[])
{
	SDL_Log("Android JNI Audio: Build %s %s", __DATE__, __TIME__);
	
	run();

	SDL_Log("Shutting down...");

	return 0;
}
