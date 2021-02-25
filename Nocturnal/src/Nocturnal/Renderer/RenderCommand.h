#pragma once
#include "RendererAPI.h"

namespace Nocturnal
{
	class RenderCommand
	{
	private:
		static RendererAPI* s_SRendererApi;
	public:
		static void SetClearColor(const glm::vec4& color) { s_SRendererApi->SetClearColor(color); }
		static void SetClearColor(const float r, const float g, const float b) { s_SRendererApi->SetClearColor({r, g, b, 1}); }
		
		static void Clear() { s_SRendererApi->Clear(); }
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { s_SRendererApi->DrawIndexed(vertexArray); }
	};
}
