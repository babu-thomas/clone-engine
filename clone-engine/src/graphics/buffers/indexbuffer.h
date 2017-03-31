#pragma once

#include <GL/glew.h>

namespace clone { namespace graphics {

	class IndexBuffer
	{
	private:
		GLuint m_bufferId;
		GLuint m_count;
	public:
		IndexBuffer(GLushort* data, GLuint count);

		void bind() const;
		void unbind() const;

		inline GLuint getCount() const { return m_count; }
	};

}
}