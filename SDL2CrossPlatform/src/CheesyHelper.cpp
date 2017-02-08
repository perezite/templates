#include "CheesyHelper.h"

#include <stdarg.h>

#include "SDL2/SDL.h"

void CheesyHelper::Log(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	SDL_Log(fmt, args);
	va_end(args);
}
