#pragma once
#include <string>
namespace Nocturnal
{
	class OpenGLShader
	{
	private:
		unsigned int _shaderId;
	
	public:
		OpenGLShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
		~OpenGLShader();

		void Bind() const;
		void UnBind() const;
		
	};
}
