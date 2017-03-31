// Ensure that glew is included before glfw
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "window.h"


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
		
		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_keys[i] = false;
		}

		for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
		{
			m_mouseButtons[i] = false;
		}
		m_mouseX = m_mouseY = 0.0;
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

	void Window::update()
	{
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error: " << error << std::endl;
		}
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	bool Window::isKeyPressed(unsigned int keycode) const
	{
		// TODO: Log this
		if (keycode >= MAX_KEYS)
		{
			return false;
		}

		return m_keys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button) const
	{
		if (button >= MAX_MOUSE_BUTTONS)
		{
			return false;
		}

		return m_mouseButtons[button];
	}

	glm::vec2 Window::getMousePosition() const
	{
		return glm::vec2(m_mouseX, m_mouseY);
	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cerr << "Failed to initialize GLFW!" << std::endl;
			return false;
		}
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
		if (!m_window)
		{
			glfwTerminate();
			std::cerr << "Failed to create GLFW window!" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, cursor_pos_callback);

		// Only initialize GLEW after making an opengl context
		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Failed to initialize GLEW!" << std::endl;
			return false;
		}

		std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

		return true;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window *win = (Window*) glfwGetWindowUserPointer(window);
		switch (action)
		{
		case GLFW_PRESS:
		case GLFW_REPEAT:
			win->m_keys[key] = true;
			break;
		case GLFW_RELEASE:
			win->m_keys[key] = false;
		default:
			break;
		}
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		switch (action)
		{
		case GLFW_PRESS:
		case GLFW_REPEAT:
			win->m_keys[button] = true;
			break;
		case GLFW_RELEASE:
			win->m_keys[button] = false;
		default:
			break;
		}
	}

	void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window *win = (Window*)glfwGetWindowUserPointer(window);
		win->m_mouseX = xpos;
		win->m_mouseY = ypos;
	}
}
}