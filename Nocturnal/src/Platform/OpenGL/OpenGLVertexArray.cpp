#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Nocturnal
{
	static GLenum ShaderTypeToGLBaseType(const ShaderType type)
	{
		switch (type)
		{
		case ShaderType::None:		return GL_FLOAT;
		case ShaderType::Float:		return GL_FLOAT;
		case ShaderType::Float2:	return GL_FLOAT;
		case ShaderType::Float3:	return GL_FLOAT;
		case ShaderType::Float4:	return GL_FLOAT;
		case ShaderType::Int:		return GL_INT;
		case ShaderType::Int2:		return GL_INT;
		case ShaderType::Int3:		return GL_INT;
		case ShaderType::Int4:		return GL_INT;
		case ShaderType::Mat3:		return GL_FLOAT;
		case ShaderType::Mat4:		return GL_FLOAT;
		case ShaderType::Bool:		return GL_BOOL;
		}
		NOC_CORE_ASSERT(false, "Shader Type not valid!");
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &mRendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &mRendererId);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(mRendererId);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		NOC_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");
		
		glBindVertexArray(mRendererId);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderTypeToGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				reinterpret_cast<const void*>(element.Offset));
			index++;
		}

		mVertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(mRendererId);
		indexBuffer->Bind();
		mIndexBuffer = indexBuffer;
	}	
}
