#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string>

#include "SDL2/SDL.h"
#include "OpenGLEngine/engine.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/log.h>

#define _USE_MATH_DEFINES

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

using namespace std;

static const int32_t POSITION_PARAMETER_INDEX = 0;
static const int32_t COLOR_PARAMETER_INDEX = 1;

int32_t shaderProgram;
float width;
float height;

GLuint LoadShader(const char *shaderSrc, GLenum type)
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);
	if(shader != 0)
	{
		// Load the shader source
		glShaderSource(shader, 1, &shaderSrc, NULL);

		// Compile the shader
		glCompileShader(shader);
		// Check the compile status
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if(!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

			if(infoLen > 1)
			{
				char* infoLog = new char[infoLen];
				glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
				LOGW("Error compiling shader:\n%s\n", infoLog);
				delete[] infoLog;
			}
			glDeleteShader(shader);
			shader = 0;
		}
	}
	return shader;
}

static int init() {
	// Initialize GL state.
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	char vShaderStr[] =
			"attribute vec4 a_vPosition;   \n"
			"attribute vec4 a_vColor;	   \n"
			"varying vec4 v_vColor;		   \n"
			"void main()                   \n"
			"{                             \n"
			"   gl_Position = a_vPosition; \n"
			"	v_vColor = a_vColor;       \n"
			"}                             \n";

	char fShaderStr[] =
			"precision mediump float;                   \n"
			"varying vec4 v_vColor;		 				\n"
			"void main()                                \n"
			"{                                          \n"
			"  gl_FragColor = v_vColor;					\n"
			"}                                          \n";

	GLuint vertexShader;
	GLuint fragmentShader;
	GLint linked;

	// Load the vertex/fragment shaders
	vertexShader = LoadShader(vShaderStr, GL_VERTEX_SHADER);
	fragmentShader = LoadShader(fShaderStr, GL_FRAGMENT_SHADER);

	// Create the program object
	shaderProgram = glCreateProgram();
	if(shaderProgram == 0)
	{
		return -1;
	}

	// Attach shaders to program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Bind a_vPosition to attribute 0 and a_vColor to 1
	glBindAttribLocation(shaderProgram, POSITION_PARAMETER_INDEX, "a_vPosition");
	glBindAttribLocation(shaderProgram, COLOR_PARAMETER_INDEX, "a_vColor");

	// Link the program
	glLinkProgram(shaderProgram);

	// Check the link status
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if(!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen > 1)
		{
			char* infoLog = new char[infoLen];
			glGetProgramInfoLog(shaderProgram, infoLen, NULL, infoLog);
			LOGW("Error linking program:\n%s\n", infoLog);

			delete[] infoLog;
		}

		glDeleteProgram(shaderProgram);
		return -1;
	}

	return 0;
}

static void display()
{ 
    static const int32_t PositionNumElements = 3;
    static const int32_t ColorNumElements = 4;
    static const int32_t VertexSize = sizeof(GLfloat) * (PositionNumElements + ColorNumElements);

	glViewport(0, 0, width, height);
    
	// Just fill the screen with a color.
    clearScreen(0.95f, 0.95f, 0.95f, 1.0f); // call from the external opengl engine

	// Use the program object
	glUseProgram(shaderProgram);
    
	glEnableVertexAttribArray(POSITION_PARAMETER_INDEX);
	glEnableVertexAttribArray(COLOR_PARAMETER_INDEX);
    
    // compute time delta in seconds
    static Uint32 previousTicks = SDL_GetTicks();
    Uint32 currentTicks = SDL_GetTicks();
    Uint32 elapsedTicks = currentTicks - previousTicks;  
    previousTicks = SDL_GetTicks();
    float deltaTime = (float)elapsedTicks / 1000.0f;
    
    // set untransformed points
    const float z = 0.0f; 
	float leftX = -0.3f;
    float leftY = -0.3f;
    float rightX = 0.3f;
    float rightY = -0.3f;
    float topX = 0.0f;
    float topY = 0.3f;
              
    // compute rotated points
    // float degToRad = (2.0f * M_PI) / 360.0f; 
    float omega = M_PI; 
    static float alpha = 0.0f;
    alpha += omega * deltaTime;
    float rotLeftX = cos(alpha)*leftX - sin(alpha)*leftY;
    float rotLeftY = sin(alpha)*leftX + cos(alpha)*leftY;
    float rotRightX = cos(alpha)*rightX - sin(alpha)*rightY;
    float rotRightY = sin(alpha)*rightX + cos(alpha)*rightY;
    float rotTopX = cos(alpha)*topX - sin(alpha)*topY;
    float rotTopY = sin(alpha)*topX + cos(alpha)*topY;
  
    // render
	const float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat triangle[] = { rotTopX, rotTopY, z,
        color[0], color[1], color[2], color[3],
        rotLeftX, rotLeftY, z,
        color[0], color[1], color[2], color[3],
        rotRightX, rotRightY, z,
        color[0], color[1], color[2], color[3] };

	glVertexAttribPointer(POSITION_PARAMETER_INDEX, PositionNumElements, GL_FLOAT, GL_FALSE, VertexSize, triangle);
	glVertexAttribPointer(COLOR_PARAMETER_INDEX, ColorNumElements, GL_FLOAT, GL_FALSE, VertexSize, &triangle[3]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
    
	glDisableVertexAttribArray(POSITION_PARAMETER_INDEX);
	glDisableVertexAttribArray(COLOR_PARAMETER_INDEX);
}


int main(int argc, char *argv[])
{    
	SDL_Window* window = 0;
	SDL_GLContext gl = 0;

	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
    
    string s = "This is a std::string";
    SDL_Log("%s\n", s.c_str());

	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
   
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(0, 0, &mode);
	width = mode.w;
	height = mode.h;

	window = SDL_CreateWindow(NULL, 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);

	if (window == 0)
	{
		SDL_Log("Failed to create window.");
		SDL_Quit();
		return 1;
	}

	gl = SDL_GL_CreateContext(window);
    
    init();
    
	Uint8 done = 0;
	SDL_Event event;
	int count = 0;
	while(!done)
	{
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN)
			{
				done = 1;
			}
		}

		SDL_Log("%d\n", count++);

        display();
             
		SDL_GL_SwapWindow(window);
		// SDL_Delay(10);
	}

	exit(0);
}
