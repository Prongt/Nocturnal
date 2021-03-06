#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLShader.h"

#include <fstream>


#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace Nocturnal
{
	OpenGLShader::OpenGLShader(const char* vertexPath, const char* fragmentPath)
	{
		//------------------------Reading Shaders from file-----------------------
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		// ensure ifstream objects can throw exceptions:
		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vertexShaderFile.open(vertexPath);
			fragmentShaderFile.open(fragmentPath);

			std::stringstream vertexShaderStream, fragmentShaderStream;

			// read file's buffer contents into streams
			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();

			vertexShaderFile.close();
			fragmentShaderFile.close();
			// convert stream into string
			vertexCode = vertexShaderStream.str();
			fragmentCode = fragmentShaderStream.str();
		}catch (std::ifstream::failure e)
		{
			NOC_CORE_FATAL("FATAL ERROR SHADER FILE CANT BE READ!");
		}
		//--------------------Compile Shaders-------------------------
		
		const GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* vertexSource = static_cast<const GLchar*>(vertexCode.c_str());
		glShaderSource(vertexShaderId, 1, &vertexSource, nullptr);

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
		vertexSource = static_cast<const GLchar*>(fragmentCode.c_str());
		glShaderSource(fragmentShaderId, 1, &vertexSource, nullptr);

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

		mShaderId = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(mShaderId, vertexShaderId);
		glAttachShader(mShaderId, fragmentShaderId);

		glLinkProgram(mShaderId);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint programLinkStatus = 0;
		glGetProgramiv(mShaderId, GL_LINK_STATUS, static_cast<int*>(&programLinkStatus));
		if (programLinkStatus == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(mShaderId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(mShaderId, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(mShaderId);
			
			glDeleteShader(vertexShaderId);
			glDeleteShader(fragmentShaderId);
			
			NOC_CORE_ERROR("{0}", infoLog.data());
			NOC_CORE_ASSERT(false, "OpenGL Program Linking Failed");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(mShaderId, vertexShaderId);
		glDetachShader(mShaderId, fragmentShaderId);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(mShaderId);
	}

	void OpenGLShader::Bind() 
	{
		glUseProgram(mShaderId);
	}

	void OpenGLShader::UnBind()
	{
		glUseProgram(0); 
	}

	void OpenGLShader::SetBool(const std::string& name, const bool value) const
	{
		glUniform1i(glGetUniformLocation(mShaderId, name.c_str()), static_cast<int>(value));
	}

	void OpenGLShader::SetInt(const std::string& name, const bool value) const
	{
		glUniform1i(glGetUniformLocation(mShaderId, name.c_str()), value);
	}

	void OpenGLShader::SetFloat(const std::string& name, const bool value) const
	{
		glUniform1f(glGetUniformLocation(mShaderId, name.c_str()), value);
	}

	void OpenGLShader::SetMatrix4(const char* uniformName, const uint32_t matrixCount, const bool transposeMatrix,
	                              const float* transformMatrix) const
	{
		glUniformMatrix4fv(glGetUniformLocation(mShaderId, uniformName), 1, GL_FALSE, transformMatrix);
	}
}
