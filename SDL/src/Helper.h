#pragma once

#include <SDL2/SDL.h>
#ifdef __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
#include <gl\glew.h>
#include <SDL2\SDL_opengl.h>
#include <gl\glu.h>
#endif

static const int32_t POSITION_PARAMETER_INDEX = 0;
static const int32_t COLOR_PARAMETER_INDEX = 1;

extern int32_t shaderProgram;

extern SDL_Window* window;

extern int height;
extern int width;

void log(const char* fmt, ...);

GLuint loadShader(const char *shaderSrc, GLenum type);

int initOpenGL();

void initSDL();

void loop(void(*render_callback)());

void cleanup();
