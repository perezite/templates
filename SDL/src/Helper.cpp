#include "Helper.h"

#include <iostream>

int32_t shaderProgram = 0;
SDL_Window* window = 0;
int height = 0;
int width = 0;

void log(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	SDL_Log(fmt, args);
	va_end(args);
}

GLuint loadShader(const char *shaderSrc, GLenum type)
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);
	if (shader != 0)
	{
		// Load the shader source
		glShaderSource(shader, 1, &shaderSrc, NULL);

		// Compile the shader
		glCompileShader(shader);
		// Check the compile status
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char* infoLog = new char[infoLen];
				glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
				std::cout << "Error compiling shader:" << std::endl << infoLog << std::endl;
				delete[] infoLog;
			}
			glDeleteShader(shader);
			shader = 0;
		}
	}
	return shader;
}

int initOpenGL() 
{
	// Initialize GL state.
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	char vShaderStr[] =
		"attribute vec4 a_vPosition;	\n"
		"attribute vec4 a_vColor;		\n"
		"varying vec4 v_vColor;			\n"
		"void main()					\n"
		"{								\n"
		"   gl_Position = a_vPosition;	\n"
		"	v_vColor = a_vColor;		\n"
		"}								\n";

	char fShaderStr[] =
#ifdef WIN32
		"#version 130								\n"
#endif
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
	vertexShader = loadShader(vShaderStr, GL_VERTEX_SHADER);
	fragmentShader = loadShader(fShaderStr, GL_FRAGMENT_SHADER);

	// Create the program object
	shaderProgram = glCreateProgram();
	if (shaderProgram == 0)
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
	if (!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = new char[infoLen];
			glGetProgramInfoLog(shaderProgram, infoLen, NULL, infoLog);
			log("Error linking program:\n%s\n", infoLog);

			delete[] infoLog;
		}

		glDeleteProgram(shaderProgram);
		return -1;
	}

	return 0;
}

void initSDL()
{
	#ifdef __ANDROID__
		SDL_GLContext gl = 0;

		if (0 != SDL_Init(SDL_INIT_VIDEO))
		{
			fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
			exit(1);
		}

		std::string s = "This is a std::string";
		log("%s\n", s.c_str());

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
			log("Failed to created window.");
			SDL_Quit();
			exit(1);
		}

		gl = SDL_GL_CreateContext(window);
	#endif

	#ifdef WIN32
		SDL_GLContext glContext;

		// initialize
		width = height = 400;
		SDL_Init(SDL_INIT_VIDEO);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		window = SDL_CreateWindow("SDL2CrossPlatform", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		glContext = SDL_GL_CreateContext(window);
		glewInit();
		SDL_GL_SetSwapInterval(1);
	#endif
}

void loop(void(*render_callback)())
{
	Uint8 done = 0;
	SDL_Event event;
	while (!done)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN)
			{
				done = 1;
			}
		}

		// display();
		render_callback();
		SDL_GL_SwapWindow(window);
	}
}

void cleanup()
{
	glDeleteProgram(shaderProgram);
	SDL_DestroyWindow(window);
	SDL_Quit();
}