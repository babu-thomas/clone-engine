#include <iostream>
#include <GL/glew.h>
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
		window.update();
	}

	return 0;
}