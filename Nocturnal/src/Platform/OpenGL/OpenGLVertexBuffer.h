#pragma once
#include "Nocturnal/Renderer/VertexBuffer.h"

namespace Nocturnal
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		void Bind() const override;
		void UnBind() const override;
	};
}
