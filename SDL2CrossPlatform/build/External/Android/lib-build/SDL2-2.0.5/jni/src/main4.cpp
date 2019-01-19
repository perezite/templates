//Using SDL, SDL_image, standard IO, and, strings
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <string.h>

Mix_Music *gMusic = NULL;

SDL_Window* gWindow = NULL;

SDL_Rect gScreenRect = { 0, 0, 320, 240 };

int main( int argc, char* args[] )
{
	//Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return -1;
    }
	
	//Get device display mode
	SDL_DisplayMode displayMode;
	if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
	{
		gScreenRect.w = displayMode.w;
		gScreenRect.h = displayMode.h;
	}

	//Create window
	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return-1;
	}

	//Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return -1;
	}
	
	//Load music
    // gMusic = Mix_LoadMUS( "beat.wav" );
    gMusic = Mix_LoadMUS( "orchestral.ogg" );	
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        return -1;
    }
   	
	//If there is no music playing
	if( Mix_PlayingMusic() == 0 )
	{
		//Play the music
		Mix_PlayMusic( gMusic, -1 );
	}
	//If music is being played
	else
	{
		//If the music is paused
		if( Mix_PausedMusic() == 1 )
		{
			//Resume the music
			Mix_ResumeMusic();
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
		}
	}
	
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;	
	
	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{   
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}
	}
	
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
	
	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	Mix_Quit();
    SDL_Quit();

	return 0;
}
