#include "NocturnalPrecompiledHeaders.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Nocturnal
{
	Shader* Shader::Create(const char* vertexPath, const char* fragmentPath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NOC_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexPath, fragmentPath);
		}

		NOC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
