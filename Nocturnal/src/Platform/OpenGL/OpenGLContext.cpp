#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>

#include "glad/glad.h"

namespace Nocturnal
{
	static GLenum ShaderTypeToGLBaseType(ShaderType type)
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
	
	OpenGLContext::OpenGLContext(struct  GLFWwindow* window)
		:WindowHandle(window)
	{
		VertexArrayObjectId = 0;
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(WindowHandle);
		const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		NOC_CORE_ASSERT(status, "Failed to initialize GLAD");


		glGenVertexArrays(1, &VertexArrayObjectId);
		glBindVertexArray(VertexArrayObjectId);
		
		//Vertices of the triangle
		//z is 0 as it is a 2d triangle 
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			BufferLayout layout = {
				{ ShaderType::Float3, "a_Position"},
				{ ShaderType::Float4, "a_Color"}
			};
			vertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for(const auto& element : layout)
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
		

		uint32_t indices[3] = { 0, 1, 2 };
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));

		
		Shader = std::make_unique<OpenGLShader>(VertexShaderSource, FragmentShaderSource);
	}

	void OpenGLContext::SwapBuffers()
	{
		Shader->Bind();
		glBindVertexArray(VertexArrayObjectId);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		
		glfwSwapBuffers(WindowHandle);
	}

	
}
