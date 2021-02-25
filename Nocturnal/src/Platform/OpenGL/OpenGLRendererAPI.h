#pragma once
#include "Nocturnal/Renderer/RendererAPI.h"

namespace Nocturnal
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Clear() override;
		void SetClearColor(const glm::vec4& color) override;
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
