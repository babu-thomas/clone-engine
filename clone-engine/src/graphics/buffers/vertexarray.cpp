#include "vertexarray.h"

namespace clone { namespace graphics {
	
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_arrayId);
	}

	VertexArray::~VertexArray()
	{
		for (int i = 0; i < m_buffers.size(); i++)
		{
			delete m_buffers[i];
		}
	}

	void VertexArray::addBuffer(Buffer *buffer, GLuint index)
	{
		bind();
		buffer->bind();
		glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(index);
		unbind();
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_arrayId);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

}
}