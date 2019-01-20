#include "Demo1.h"
#include "Helper.h"
#include "MathHelper.h"
using namespace Math;

namespace
{
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
		float rotLeftX = cosf(alpha)*leftX - sinf(alpha)*leftY;
		float rotLeftY = sinf(alpha)*leftX + cosf(alpha)*leftY;
		float rotRightX = cosf(alpha)*rightX - sinf(alpha)*rightY;
		float rotRightY = sinf(alpha)*rightX + cosf(alpha)*rightY;
		float rotTopX = cosf(alpha)*topX - sinf(alpha)*topY;
		float rotTopY = sinf(alpha)*topX + cosf(alpha)*topY;

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
}

void Demo1::run()
{
	initSDL();
	initOpenGL();

	loop(&display);

	cleanup();
}
