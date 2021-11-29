#include "VertexBuffer.h"

namespace nc
{
	VertexBuffer::~VertexBuffer()
	{
		//<if vao is not 0 then glDeleteVertexArrays>
		//	<if vbo is not 0 then glDeleteBuffers>
		if (vao != 0)
		{
			glDeleteVertexArrays(vertexCount, &vao);
		}
		if (vbo != 0)
		{
			glDeleteBuffers(vertexCount, &vbo);
		}
	}

	bool VertexBuffer::Load(const std::string& name, void* null)
	{
		//<glGenVertexArrays with vao>
		//	<glBindVertexArray vao>
		glGenVertexArrays(vertexCount, &vao);
		glBindVertexArray(vao);

			return true;
	}

	void VertexBuffer::CreateVertexBuffer(GLsizei size, GLsizei vertexCount, void* data)
	{
		this->vertexCount = vertexCount;
		//<glGenBuffers with vbo>
		//	<glBindBuffer GL_ARRAY_BUFFER with vbo>
		glGenBuffers(vertexCount, &vbo);
		glBindBuffer(vbo, GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::SetAttribute(int index, GLint size, GLsizei stride, size_t offset)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
	}

	void VertexBuffer::Draw(GLenum primitiveType)
	{
		//<glBindVertexArray vao>
		//	<glDrawArrays use vertex count>
		glBindVertexArray(vao);
		glDrawArrays(primitiveType, 0, vertexCount);
	}
}