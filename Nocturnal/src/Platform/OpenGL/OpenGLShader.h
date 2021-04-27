#pragma once

#include "Nocturnal/Renderer/Shader.h"

namespace Nocturnal
{
	class OpenGLShader :public Shader
	{
	private:
		unsigned int mShaderId;
	
	public:
		OpenGLShader(const char* vertexPath, const char* fragmentPath);
		virtual ~OpenGLShader();

		void Bind() override;
		void UnBind() override;

		void SetBool(const std::string& name, bool value) const override;
		void SetInt(const std::string& name, int value) const override;
		void SetFloat(const std::string& name, float value) const override;
		void SetMatrix4(const char* uniformName, const uint32_t matrixCount, const bool transposeMatrix,
		                const float* transformMatrix) const override;
		void SetVec3(const std::string& name, const glm::vec3& value) const override;
		void SetVec4(const std::string& name, const glm::vec4& value) const override;
	};
}
