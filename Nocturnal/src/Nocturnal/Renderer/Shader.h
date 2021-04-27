#pragma once
#include <string>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace Nocturnal
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void SetBool(const std::string& name, bool value)const = 0;
		virtual void SetInt(const std::string& name, int value)const = 0;
		virtual void SetFloat(const std::string& name, float value)const = 0;
		virtual void SetVec3(const std::string& name, const glm::vec3& value)const = 0;
		virtual void SetVec4(const std::string& name, const glm::vec4& value)const = 0;
		virtual void SetMatrix4(const char* uniformName, const uint32_t matrixCount, const bool transposeMatrix, const float* transformMatrix)const = 0;

		static Shader* Create(const char* vertexPath, const char* fragmentPath);
	};
}
