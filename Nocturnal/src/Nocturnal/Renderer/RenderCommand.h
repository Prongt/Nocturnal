#pragma once
#include "RendererAPI.h"

namespace Nocturnal
{
	class RenderCommand
	{
	private:
		static RendererAPI* s_RendererApi;
	public:
		static void SetClearColor(const glm::vec4& color) { s_RendererApi->SetClearColor(color); }
		static void SetClearColor(const float r, const float g, const float b) { s_RendererApi->SetClearColor({r, g, b, 1}); }
		
		static void Clear() { s_RendererApi->Clear(); }
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { s_RendererApi->DrawIndexed(vertexArray); }

		//TODO Remove GetTime from RenderCommand and move to Time class
		static float GetTime() { return s_RendererApi->GetTime(); }
	};
}
