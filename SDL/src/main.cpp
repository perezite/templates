#include "SDL2/SDL.h"
#include <iostream>
#include <stdlib.h>

#undef main					// prevent LNK4098 warning in VC2010	

/*
int main(int argc, char *argv[]) 
{
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *bitmapTex = NULL;
    SDL_Surface *bitmapSurface = NULL;
    int posX = 100, posY = 100, width = 320, height = 240;

    win = SDL_CreateWindow("Hello World", posX, posY, width, height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    bitmapSurface = SDL_LoadBMP("hello.bmp");
    bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
    SDL_FreeSurface(bitmapSurface);

	// check window resolution
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	std::cout << w << " " << h << " " << std::endl;

    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(bitmapTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    return 0;
}
*/

int main(int argc, char *argv[]) 
{
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *bitmapTex = NULL;
    SDL_Surface *bitmapSurface = NULL;

	SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, 
									&win, &renderer);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");  
	SDL_RenderSetLogicalSize(renderer, 200, 100);

    bitmapSurface = SDL_LoadBMP("helloHD.bmp");
    bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
    SDL_FreeSurface(bitmapSurface);

	// check window resolution
	int wPhysical, hPhysical;
	int wLogical, hLogical;
	SDL_GetWindowSize(win, &wPhysical, &hPhysical);
	SDL_RenderGetLogicalSize(renderer, &wLogical, &hLogical);
	std::cout << "physical size: " << wPhysical << " " << hPhysical << " " << std::endl;
	std::cout << "logical size: " << wLogical << " " << hLogical << " " << std::endl;

	// do rendering
	SDL_RenderClear(renderer);
	SDL_Rect dstrect;
	dstrect.x = 0; dstrect.y = 0; dstrect.w = 50; dstrect.h = 50;
	//SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
	SDL_RenderCopy(renderer, bitmapTex, NULL, &dstrect);
	SDL_RenderPresent(renderer);
	SDL_Delay(3000);

	// cleanup
    SDL_DestroyTexture(bitmapTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

	system("pause");

    return 0;
	
}





