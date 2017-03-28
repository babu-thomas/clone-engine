#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "src/graphics/window.h"

// To enable NVIDIA Graphics card
//extern "C" {
//	_declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
//}

int main()
{
	using namespace clone;
	using namespace graphics;

	Window window("Clone Engine!", 800, 600);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	while (!window.closed())
	{
		window.clear();
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
		window.update();
	}

	return 0;
}