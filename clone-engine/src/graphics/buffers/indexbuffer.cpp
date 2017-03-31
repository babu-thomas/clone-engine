#include "indexbuffer.h"

namespace clone { namespace graphics {
	
	IndexBuffer::IndexBuffer(GLushort *data, GLuint count)
		: m_count(count)
	{
		glGenBuffers(1, &m_bufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
	}
	
	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
}