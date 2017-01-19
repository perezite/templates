#include "engine.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

int clearScreen(const float r, const float g, const float b, const float a)
{
   glClearColor(r, g, b, a);
   glClear(GL_COLOR_BUFFER_BIT);
}