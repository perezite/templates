#include "Demo2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <string.h>
#ifdef WIN32
	#include <Windows.h>
#endif

namespace
{
	//Texture wrapper class
	class LTexture
	{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile(std::string path);

		//Creates blank texture
		bool createBlank(int width, int height, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);

		//Renders texture at given point
		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Set self as render target
		void setAsRenderTarget();

		//Gets image dimensions
		int getWidth();
		int getHeight();

		//Pixel manipulators
		bool lockTexture();
		bool unlockTexture();
		void* getPixels();
		void copyPixels(void* pixels);
		int getPitch();
		Uint32 getPixel32(unsigned int x, unsigned int y);

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		void* mPixels;
		int mPitch;

		//Image dimensions
		int mWidth;
		int mHeight;
	};

	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Screen dimensions
	SDL_Rect gScreenRect = { 0, 0, 320, 240 };

	//Scene textures
	LTexture gPortraitTexture;	
	LTexture gLandscapeTexture;

	//The music
	Mix_Music *gMusic = NULL;

	// a sound effect
	Mix_Chunk *gSound = NULL;


	LTexture::LTexture()
	{
		//Initialize
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		mPixels = NULL;
		mPitch = 0;
	}

	LTexture::~LTexture()
	{
		//Deallocate
		free();
	}

	bool LTexture::loadFromFile(std::string path)
	{
		//Get rid of preexisting texture
		free();

		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else
		{
			//Convert surface to display format
			SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
			if (formattedSurface == NULL)
			{
				SDL_Log("Unable to convert loaded surface to display format! %s\n", SDL_GetError());
			}
			else
			{
				//Create blank streamable texture
				newTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
				if (newTexture == NULL)
				{
					SDL_Log("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
				}
				else
				{
					//Enable blending on texture
					SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

					//Lock texture for manipulation
					SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &mPixels, &mPitch);

					//Copy loaded/formatted surface pixels
					memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);
					
					//Get image dimensions
					mWidth = formattedSurface->w;
					mHeight = formattedSurface->h;

					//Get pixel data in editable format
					Uint32* pixels = (Uint32*)mPixels;
					int pixelCount = (mPitch / 4) * mHeight;

					//Map colors
					Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0, 0xFF, 0xFF);
					Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00);

					//Color key pixels
					for (int i = 0; i < pixelCount; ++i)
					{
						if (pixels[i] == colorKey)
						{
							pixels[i] = transparent;
						}
					}

					//Unlock texture to update
					SDL_UnlockTexture(newTexture);
					mPixels = NULL;
				}

				//Get rid of old formatted surface
				SDL_FreeSurface(formattedSurface);
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		//Return success
		mTexture = newTexture;
		return mTexture != NULL;
	}

	bool LTexture::createBlank(int width, int height, SDL_TextureAccess access)
	{
		//Create uninitialized texture
		mTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
		if (mTexture == NULL)
		{
			SDL_Log("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = width;
			mHeight = height;
		}

		return mTexture != NULL;
	}

	void LTexture::free()
	{
		//Free texture if it exists
		if (mTexture != NULL)
		{
			SDL_DestroyTexture(mTexture);
			mTexture = NULL;
			mWidth = 0;
			mHeight = 0;
			mPixels = NULL;
			mPitch = 0;
		}
	}

	void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
	{
		//Modulate texture rgb
		SDL_SetTextureColorMod(mTexture, red, green, blue);
	}

	void LTexture::setBlendMode(SDL_BlendMode blending)
	{
		//Set blending function
		SDL_SetTextureBlendMode(mTexture, blending);
	}

	void LTexture::setAlpha(Uint8 alpha)
	{
		//Modulate texture alpha
		SDL_SetTextureAlphaMod(mTexture, alpha);
	}

	void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
	{
		//Set rendering space and render to screen
		SDL_Rect renderQuad = { x, y, mWidth, mHeight };

		//Set clip rendering dimensions
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		//Render to screen
		SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
	}

	void LTexture::setAsRenderTarget()
	{
		//Make self render target
		SDL_SetRenderTarget(gRenderer, mTexture);
	}

	int LTexture::getWidth()
	{
		return mWidth;
	}

	int LTexture::getHeight()
	{
		return mHeight;
	}

	bool LTexture::lockTexture()
	{
		bool success = true;

		//Texture is already locked
		if (mPixels != NULL)
		{
			SDL_Log("Texture is already locked!\n");
			success = false;
		}
		//Lock texture
		else
		{
			if (SDL_LockTexture(mTexture, NULL, &mPixels, &mPitch) != 0)
			{
				SDL_Log("Unable to lock texture! %s\n", SDL_GetError());
				success = false;
			}
		}

		return success;
	}

	bool LTexture::unlockTexture()
	{
		bool success = true;

		//Texture is not locked
		if (mPixels == NULL)
		{
			SDL_Log("Texture is not locked!\n");
			success = false;
		}
		//Unlock texture
		else
		{
			SDL_UnlockTexture(mTexture);
			mPixels = NULL;
			mPitch = 0;
		}

		return success;
	}

	void* LTexture::getPixels()
	{
		return mPixels;
	}

	void LTexture::copyPixels(void* pixels)
	{
		//Texture is locked
		if (mPixels != NULL)
		{
			//Copy to locked pixels
			memcpy(mPixels, pixels, mPitch * mHeight);
		}
	}

	int LTexture::getPitch()
	{
		return mPitch;
	}

	Uint32 LTexture::getPixel32(unsigned int x, unsigned int y)
	{
		//Convert the pixels to 32 bit
		Uint32 *pixels = (Uint32*)mPixels;

		//Get the pixel requested
		return pixels[(y * (mPitch / 4)) + x];
	}

	std::string getFilePathFromAssetPath(std::string assetPath)
	{
		#ifdef __ANDROID__
			return assetPath;
		#elif defined(WIN32)
			wchar_t filePath[MAX_PATH];
			HMODULE hModule = GetModuleHandle(NULL);
			GetModuleFileName(hModule, filePath, (sizeof(filePath)));
			std::wstring filePathAsWideString(filePath);
			std::string filePathAsString(filePathAsWideString.begin(), filePathAsWideString.end());
			size_t lastPathSeparatorPosition = filePathAsString.rfind("\\");
			std::string executableFolderPath = filePathAsString.substr(0, lastPathSeparatorPosition);
			std::string assetFolderPath = executableFolderPath + "\\..\\Assets";
			return assetFolderPath + "\\" + assetPath;
		#else
			#error OS not supported
		#endif	
	}

	bool init()
	{
		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Set texture filtering to linear
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				SDL_Log("Warning: Linear texture filtering not enabled!");
			}

			//Get device display mode
			SDL_DisplayMode displayMode;
			if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0)
			{
				#ifdef WIN32
					gScreenRect.w = 400;
					gScreenRect.h = 400;
				#else			
				gScreenRect.w = displayMode.w;
				gScreenRect.h = displayMode.h;
				#endif
			}

			//Create window
			gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
			if (gWindow == NULL)
			{
				SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Create renderer for window
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (gRenderer == NULL)
				{
					SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						SDL_Log("SDL_image could not initialize! %s\n", IMG_GetError());
						success = false;
					}
					else
					{
						//Initialize SDL_mixer
						if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
						{
							SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
							success = false;
						}
						else
						{
							//Load music
							gMusic = Mix_LoadMUS(getFilePathFromAssetPath("orchestral.ogg").c_str());
							if (gMusic == NULL)
							{
								SDL_Log("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
								success = false;
							}
							else
							{
								//Load sound
								gSound = Mix_LoadWAV(getFilePathFromAssetPath("ding.wav").c_str());
								if (gSound == NULL)
								{
									SDL_Log("Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError());
									success = false;
								}
							}
						}
					}
				}
			}
		}

		return success;
	}

	bool loadMedia()
	{
		//Loading success flag
		bool success = true;

		//Load splash textures
		if (!gPortraitTexture.loadFromFile(getFilePathFromAssetPath("portrait.png").c_str()))
		{
			SDL_Log("Failed to load portrait texture!\n");
			success = false;
		}
		if (!gLandscapeTexture.loadFromFile(getFilePathFromAssetPath("landscape.png").c_str()))
		{
			SDL_Log("Failed to load landscape texture!\n");
			success = false;
		}

		return success;
	}

	void close()
	{
		// Free the sound 
		Mix_FreeChunk(gSound);
		gSound = NULL;

		//Free the music
		Mix_FreeMusic(gMusic);
		gMusic = NULL;

		//Free loaded images
		gPortraitTexture.free();
		gLandscapeTexture.free();

		//Destroy window
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
		gRenderer = NULL;

		//Quit SDL subsystems
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}

}

void Demo2::run()
{
	//Start up SDL and create window
	if (!init())
	{
		SDL_Log("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			SDL_Log("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//touch event
					if (e.type == SDL_FINGERDOWN || e.type == SDL_KEYDOWN) 
					{
						Mix_PlayChannel(-1, gSound, 0);
					}

					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//Window event
					else if (e.type == SDL_WINDOWEVENT)
					{
						//Window resize/orientation change
						if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
						{
							//Get screen dimensions
							gScreenRect.w = e.window.data1;
							gScreenRect.h = e.window.data2;

							//Update screen
							SDL_RenderPresent(gRenderer);
						}
					}
				}

				//If there is no music playing
				if (Mix_PlayingMusic() == 0)
				{
					//Play the music
					Mix_PlayMusic(gMusic, -1);
				}
				//If music is being played
				else
				{
					//If the music is paused
					if (Mix_PausedMusic() == 1)
					{
						//Resume the music
						Mix_ResumeMusic();
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render splash
				if (gScreenRect.h >= gScreenRect.w)
				{
					gPortraitTexture.render((gScreenRect.w - gPortraitTexture.getWidth()) / 2, (gScreenRect.h - gPortraitTexture.getHeight()) / 2);
				}
				else
				{
					gLandscapeTexture.render((gScreenRect.w - gLandscapeTexture.getWidth()) / 2, (gScreenRect.h - gLandscapeTexture.getHeight()) / 2);
				}

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	::close();

}
