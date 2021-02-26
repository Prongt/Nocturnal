#pragma once
#include <string>

namespace Nocturnal
{
	class OpenGLShader
	{
	private:
		unsigned int _ShaderId;
	
	public:
		OpenGLShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
		~OpenGLShader();

		void Bind() const;
		void UnBind() const;


		void ApplyMatrixToUniform(char* uniformName, uint32_t matrixCount, bool transposeMatrix, float* transformMatrix);
		static float GetTime();
	};
}
