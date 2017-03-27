#include "window.h"
#include <iostream>

namespace clone { namespace graphics {
	Window::Window(const std::string& title, int width, int height)
	{
		m_title = title;
		m_width = width;
		m_height = height;
		if (!init())
		{
			glfwTerminate();
		}
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_window);
	}

	// TODO: Maybe make the renderer do this
	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update() const
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
		if (!m_window)
		{
			glfwTerminate();
			std::cout << "Failed to create GLFW window!" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_window);
		return true;
	}

}
}