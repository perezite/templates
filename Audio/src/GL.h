#ifdef  WIN32
	#include <gl/glew.h>
	#include <SDL2/SDL_opengl.h>
	#include <gl/glu.h>
#else
	#include <GLES2/gl2.h>	
	#include <GLES2/gl2ext.h>
#endif 