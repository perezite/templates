#include "engine.h"

#ifdef ANDROID
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
#endif
#ifdef _WIN32
	#include <windows.h>
	#include <GL/gl.h>
#endif

int clearScreen(const float r, const float g, const float b, const float a)
{
   glClearColor(r, g, b, a);
   glClear(GL_COLOR_BUFFER_BIT);
   return 0;
}