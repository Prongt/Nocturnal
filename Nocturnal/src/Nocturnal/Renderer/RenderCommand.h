#pragma once
#include "RendererAPI.h"

namespace Nocturnal
{
	class RenderCommand
	{
	private:
		static RendererAPI* sRendererApi;
	public:
		static void SetClearColor(const glm::vec4& color) { sRendererApi->SetClearColor(color); }
		static void SetClearColor(const float r, const float g, const float b) { sRendererApi->SetClearColor({r, g, b, 1}); }
		
		static void Clear() { sRendererApi->Clear(); }
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { sRendererApi->DrawIndexed(vertexArray); }

		static RendererAPI* GetRenderApi() { return sRendererApi; }
	};
}
