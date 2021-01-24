#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>

#include "glad/glad.h"

namespace Nocturnal
{
	OpenGLContext::OpenGLContext(class GLFWwindow* window)
		:WindowHandle(window)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(WindowHandle);
		const int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NOC_CORE_ASSERT(status, "Failed to initialize GLAD");

		//Vertices of the triangle
		//z is 0 as it is a 2d triangle 
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

		glGenVertexArrays(1, &VertexArrayObjectID);
		glBindVertexArray(VertexArrayObjectID);

		//Creating buffer and Generating id for the vertex buffer
		unsigned int VertexBufferID;
		glGenBuffers(1, &VertexBufferID);

		//Binding the vertex buffer to type GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);

		//Allocates memory on the gpu and sends the vertex data
		//GL_STATIC_DRAW -> the data is set only once and used many times
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Creating shader and generating shader id
		unsigned int VertexShaderID;
		VertexShaderID = glCreateShader(GL_VERTEX_SHADER);

		//Compiling shader from shader source
		glShaderSource(VertexShaderID, 1, &vertexShaderSource, NULL);
		glCompileShader(VertexShaderID);

		int shaderCompileSuccess;
		char infoLog[512];
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &shaderCompileSuccess);

		if (!shaderCompileSuccess)
		{
			glGetShaderInfoLog(VertexShaderID, 512, NULL, infoLog);
			NOC_ERROR("Vertex Shader Compile Failed", infoLog);
		}

		unsigned int FragmentShaderID;
		FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentShaderID, 1, &fragmentShaderSource, NULL);
		glCompileShader(FragmentShaderID);

		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &shaderCompileSuccess);

		if (!shaderCompileSuccess)
		{
			glGetShaderInfoLog(FragmentShaderID, 512, NULL, infoLog);
			NOC_ERROR("Fragment Shader Compile Failed", infoLog);
		}

		
		ShaderProgramID = glCreateProgram();

		glAttachShader(ShaderProgramID, VertexShaderID);
		glAttachShader(ShaderProgramID, FragmentShaderID);
		glLinkProgram(ShaderProgramID);

		glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &shaderCompileSuccess);
		if (!shaderCompileSuccess)
		{
			glGetProgramInfoLog(ShaderProgramID, 512, NULL, infoLog);
			NOC_ERROR("Shader Program Linking Failed", infoLog);
		}

		glUseProgram(ShaderProgramID);
		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		//first index is 0
		//Every 3 elements in the array is a vertex
		//Each position is of type float,
		//Dont normailze values to whole numbers
		//Each vertex requires 3 floats of memory allocation
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void OpenGLContext::SwapBuffers()
	{
		glUseProgram(ShaderProgramID);
		glBindVertexArray(VertexArrayObjectID);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(WindowHandle);
	}

	
}
