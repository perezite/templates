#include "CheesyHelper.h"

#include <SDL.h>

#include <stdarg.h>

void CheesyHelper::Log(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	SDL_Log(fmt, args);
	va_end(args);
}

void CheesyHelper::ShowMessageBox(std::string title, std::string message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), NULL);
}
