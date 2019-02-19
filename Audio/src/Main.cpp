#include "Window.h"
#include "Input.h"
#include "Sound.h"
#include "Music.h"
#include "Stopwatch.h"
#include "Logger.h"
#include "Asset.h"
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

PlaybackState playbackState = PlaybackState::TheBeginning;
PlaybackState nextPlaybackState = PlaybackState::OneSoundOneMusic;
bool isMusicFading = false;
sb::Sound sound1;
sb::Sound sound2;
sb::Music music1;
sb::Music music2;
sb::Music music3;

void TheBeginning(PlaybackState next)
{
	SDL_Log("TheBeginning update");
	static int counter = 0;
	counter++;
	if (counter == 1) {
		SDL_Log("TheBeginning finished");
		nextPlaybackState = next;
	}
}

void TwoSoundsTwoFadingMusics(PlaybackState next)
{
	SDL_Log("TowSoundsTwoFadingMusics update");
	static int counter = 0;
	if (counter == 0) {
		music1.setLooping(true);
		music2.setLooping(true);
		music1.setVolume(0);
		music2.setVolume(1);
		isMusicFading = true;
	}

	music1.play();
	music2.play();
	sound1.play();
	SDL_Log("0.5 second delay...");
	SDL_Delay(500);
	SDL_Log("Done");
	sound2.play();
	counter++;
	if (counter == 3) {
		SDL_Log("TowSoundsTwoFadingMusics finished");
		music1.setVolume(1);
		music2.setVolume(1);
		music1.stop();
		music2.stop();
		isMusicFading = false;
		nextPlaybackState = next;
	}
}

void TwoFadingMusics(PlaybackState next)
{
	SDL_Log("TwoFadingMusics update");
	static int counter = 0;
	if (counter == 0) {
		music1.setVolume(0);
		music2.setVolume(1);
		music1.play();
		music2.play();
		isMusicFading = true;
	}
	counter++;
	if (counter == 2) {
		SDL_Log("TwoFadingMusics finished");
		music1.setVolume(1);
		music2.setVolume(1);
		music1.stop();
		music2.stop();
		isMusicFading = false;
		nextPlaybackState = next;
	}
}

void LoopingMusic(PlaybackState next)
{
	SDL_Log("LoopingMusic update");
	static int counter = 0;
	music3.play();

	counter++;
	if (counter == 2) {
		SDL_Log("LoopingMusic finished");
		music3.stop();
		nextPlaybackState = next;
	}
}

void TwoMusicsTwoSounds(PlaybackState next)
{
	SDL_Log("TwoMusicsTwoSounds update");
	static unsigned int counter = 0;
	music1.play();
	music2.play();
	sound2.play();
	SDL_Log("0.5 second delay...");
	SDL_Delay(500);
	SDL_Log("Done");
	sound1.play();
	counter++;
	if (counter == 3) {
		SDL_Log("TwoMusicsTwoSounds finished");
		music1.stop();
		music2.stop();
		nextPlaybackState = next;
	}
}

void TwoMusics(PlaybackState next)
{
	SDL_Log("TwoMusics update");
	static unsigned int counter = 0;
	music2.play();
	music1.play();
	counter++;
	if (counter == 2) {
		SDL_Log("TwoMusics finished");
		music1.stop();
		music2.stop();
		nextPlaybackState = next;
	}
}

void TwoSounds(PlaybackState next)
{
	SDL_Log("TwoSounds update");
	static unsigned int counter = 0;
	sound2.play();
	SDL_Log("0.5 second delay...");
	SDL_Delay(500);
	SDL_Log("Done");
	sound1.play();
	counter++;
	if (counter == 3) {
		SDL_Log("TwoSounds finished");
		nextPlaybackState = next;
	}
}

void OneSoundOneMusic(PlaybackState next)
{
	SDL_Log("OneSoundOneMusic update");
	static unsigned int counter = 0;
	music1.play();
	sound1.play();
	counter++;
	if (counter == 3) {
		SDL_Log("OneSoundOneMusic finished");
		music1.stop();
		nextPlaybackState = next;
	}
}

void OneMusic(PlaybackState next)
{
	SDL_Log("OneMusic update");
	static unsigned int counter = 0;
	music2.stop();
	music1.play();
	counter++;
	if (counter == 2) {
		SDL_Log("OneMusic finished");
		music1.stop();
		music2.stop();
		nextPlaybackState = next;
	}
}

void OneSound(PlaybackState next)
{
	SDL_Log("OneSound update");
	static unsigned int counter = 0;
	sound1.play();
	counter++;
	if (counter == 3) {
		SDL_Log("OneSound finished");
		nextPlaybackState = next;
	}
}

void TheEnd()
{
	SDL_Log("The end");
	music1.stop();
}

void playback() {

	playbackState = nextPlaybackState;

	if (playbackState == PlaybackState::TheBeginning)
		TheBeginning(PlaybackState::TowSoundsTwoFadingMusics);
	else if (playbackState == PlaybackState::TowSoundsTwoFadingMusics)
		TwoSoundsTwoFadingMusics(PlaybackState::TwoFadingMusics);
	else if (playbackState == PlaybackState::TwoFadingMusics)
		TwoFadingMusics(PlaybackState::LoopingMusic);
	else if (playbackState == PlaybackState::LoopingMusic)
		LoopingMusic(PlaybackState::TwoMusicsTwoSounds);
	else if (playbackState == PlaybackState::TwoMusicsTwoSounds)
		TwoMusicsTwoSounds(PlaybackState::TwoMusics);
	else if (playbackState == PlaybackState::TwoMusics)
		TwoMusics(PlaybackState::TwoSounds);
	else if (playbackState == PlaybackState::TwoSounds)
		TwoSounds(PlaybackState::OneSoundOneMusic);
	else if (playbackState == PlaybackState::OneSoundOneMusic)
		OneSoundOneMusic(PlaybackState::OneMusic);
	else if (playbackState == PlaybackState::OneMusic)
		OneMusic(PlaybackState::OneSound);
	else if (playbackState == PlaybackState::OneSound)
		OneSound(PlaybackState::TheEnd);
	else if (playbackState == PlaybackState::TheEnd) 
		TheEnd();
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
}

void updatePlayback()
{
	if (isMusicFading)
		fadeMusics();
}

void init()
{	
	sound1.load(sb::Asset("ding.ogg").getFilePath());
	sound2.load(sb::Asset("losing.wav").getFilePath());
	music1.load(sb::Asset("ukulele.ogg").getFilePath());
	music2.load(sb::Asset("idea.ogg").getFilePath());
	music3.load(sb::Asset("losing.ogg").getFilePath());
	music3.setLooping(true);
}

void update()
{
	if (sb::Input::isMouseGoingDown() || sb::Input::isTouchGoingDown()) {
		SDL_Log("tap");
		playback();
	}

	updatePlayback();
}

void run() 
{
	sb::Window window;
	init();

	while (window.isOpen()) {
		window.update();
		update();
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
