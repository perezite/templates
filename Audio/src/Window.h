#pragma once

#include "GL.h"
#include <SDL2/SDL.h>

namespace sb
{
	class Window
	{
	public:
		Window(int width = 400, int height = 400);

		~Window();

		bool isOpen() { return m_isOpen; }

		void update();

		void draw();

		void close() { m_isOpen = false; }

	private:
		bool m_isOpen;

		SDL_Window* m_sdlWindow;

		SDL_GLContext m_glContext;
	};
}