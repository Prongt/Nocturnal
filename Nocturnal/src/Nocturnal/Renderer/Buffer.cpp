#include "NocturnalPrecompiledHeaders.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Nocturnal		
{
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			NOC_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}

		NOC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			NOC_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		NOC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
