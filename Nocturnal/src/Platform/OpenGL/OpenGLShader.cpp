#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLShader.h"
#include "glad/glad.h"

namespace Nocturnal
{
	OpenGLShader::OpenGLShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
	{
		const GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* vertexSource = static_cast<const GLchar*>(vertexShaderSrc.c_str());
		glShaderSource(vertexShaderId, 1, &vertexSource, 0);

		glCompileShader(vertexShaderId);

		GLint shaderCompileSuccess = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &shaderCompileSuccess);
		if (shaderCompileSuccess == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShaderId, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShaderId);

			NOC_CORE_ERROR("{0}", infoLog.data());
			NOC_CORE_ASSERT(false, "OpenGL Vertex Shader Failed");
			return;
		}

		const GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		vertexSource = static_cast<const GLchar*>(fragmentShaderSrc.c_str());
		glShaderSource(fragmentShaderId, 1, &vertexSource, 0);

		glCompileShader(fragmentShaderId);

		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &shaderCompileSuccess);
		if (shaderCompileSuccess == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShaderId, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShaderId);
			glDeleteShader(vertexShaderId);

			NOC_CORE_ERROR("{0}", infoLog.data());
			NOC_CORE_ASSERT(false, "OpenGL Fragment Shader Failed");
			return;
		}

		ShaderId = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(ShaderId, vertexShaderId);
		glAttachShader(ShaderId, fragmentShaderId);

		glLinkProgram(ShaderId);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint programLinkStatus = 0;
		glGetProgramiv(ShaderId, GL_LINK_STATUS, static_cast<int*>(&programLinkStatus));
		if (programLinkStatus == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(ShaderId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(ShaderId, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(ShaderId);
			
			glDeleteShader(vertexShaderId);
			glDeleteShader(fragmentShaderId);
			
			NOC_CORE_ERROR("{0}", infoLog.data());
			NOC_CORE_ASSERT(false, "OpenGL Program Linking Failed");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(ShaderId, vertexShaderId);
		glDetachShader(ShaderId, fragmentShaderId);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(ShaderId);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(ShaderId);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0); 
	}
}
