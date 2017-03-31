#pragma once

#include <GL/glew.h>

namespace clone { namespace graphics {

	class Buffer
	{
	private:
		GLuint m_bufferId;
		GLuint m_componentCount;
	public:
		Buffer(GLfloat* data, GLuint count, GLuint componentCount);

		void bind() const;
		void unbind() const;

		inline GLuint getComponentCount() const { return m_componentCount; }
	};

}
}