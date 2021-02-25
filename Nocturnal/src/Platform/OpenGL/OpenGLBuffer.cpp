#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace Nocturnal
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &rendererID);

		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
		
		//Allocates memory on the gpu and sends the vertex data
		//GL_STATIC_DRAW -> the data is set only once and used many times
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: indicesCount(count)
	{
		glCreateBuffers(1, &rendererID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);

		//Allocates memory on the gpu and sends the vertex data
		//GL_STATIC_DRAW -> the data is set only once and used many times
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}