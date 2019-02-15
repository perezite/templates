#include "Input.h"
#include <SDL2/SDL.h>

namespace sb
{
	bool Input::m_hasQuitEvent = false;

	bool Input::m_mouseGoingDown = false;

	bool Input::m_touchGoingDown = false;

	void Input::update()
	{
		SDL_Event event;

		m_mouseGoingDown = false;
		m_touchGoingDown = false;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) 
				m_hasQuitEvent = true;

			if (event.type == SDL_MOUSEBUTTONDOWN) 
				m_mouseGoingDown = true;

			if (event.type == SDL_FINGERDOWN)
				m_touchGoingDown = true;
		}
	}
}


