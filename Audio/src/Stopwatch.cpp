#include "Stopwatch.h"

namespace sb
{
	Stopwatch::Stopwatch()
	{
		reset();
	}

	void Stopwatch::reset()
	{
		m_startTicks = SDL_GetTicks();
	}

	float Stopwatch::getElapsedMs()
	{
		return  float(SDL_GetTicks() - m_startTicks);
	}

	float Stopwatch::getElapsedSeconds()
	{
		return getElapsedMs() / 1000.0f;
	}
}
