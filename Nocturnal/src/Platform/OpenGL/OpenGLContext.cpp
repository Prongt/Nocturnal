#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>

#include "glad/glad.h"

namespace Nocturnal
{
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
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		//first index is 0
		//Every 3 elements in the array is a vertex
		//Each position is of type float,
		//Dont normailze values to whole numbers
		//Each vertex requires 3 floats of memory allocation
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		
		

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
