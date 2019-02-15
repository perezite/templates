////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Audio.hpp>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "Window.h"
#include "Input.h"

int main()
{
	sb::Window window;

	sf::Music music;
	music.openFromFile("D:\\testing\\SFML-Audio\\Solution\\SFMLAudio\\Debug\\resources\\orchestral.ogg");
	music.play();

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	int result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_Chunk* sound = Mix_LoadWAV("ding.ogg");

	while(window.isOpen()){
		if (sb::Input::isMouseGoingDown()) {
			int result = Mix_PlayChannel(-1, sound, 0);
		}

		window.update();
	}
}
