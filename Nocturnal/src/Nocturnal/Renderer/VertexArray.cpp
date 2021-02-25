#include "NocturnalPrecompiledHeaders.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Nocturnal
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NOC_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		NOC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
