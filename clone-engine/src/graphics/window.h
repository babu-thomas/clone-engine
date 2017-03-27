#pragma once

#include <string>
#include <GLFW/glfw3.h>

namespace clone { namespace graphics {

	class Window
	{
	private:
		std::string m_title;
		int m_width, m_height;
		GLFWwindow *m_window;
		bool m_closed;

	public:
		Window(const std::string& name, int width, int height);
		~Window();
		bool closed() const;
		void clear() const;
		void update() const;

	private:
		bool init();
	};
}
}