#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string>
#include <iostream>
using namespace std;

#include "Helper.h"
#include "MathHelper.h"
using namespace Math;

#define _USE_MATH_DEFINES
#ifdef __ANDROID__
	#define main SDL_main
#endif
#ifdef WIN32
	#undef main
#endif

static void display()
{
	static const int32_t PositionNumElements = 3;
	static const int32_t ColorNumElements = 4;
	static const int32_t VertexSize = sizeof(GLfloat) * (PositionNumElements + ColorNumElements);

	glViewport(0, 0, width, height);

	// Just fill the screen with a color.
	glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

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
	float omega = MathHelper::GetPi();
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

int main(int argc, char* args[])
{
	initSDL();
	initOpenGL();

	loop(&display);

	cleanup();
	exit(0);
}
