#include "NocturnalPrecompiledHeaders.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Nocturnal
{
	Texture* Texture::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NOC_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLTexture(path);
		}

		NOC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
