#pragma once
#include "Nocturnal/Renderer/VertexArray.h"
#include <memory>

namespace Nocturnal
{
	class OpenGLVertexArray : public VertexArray
	{
	private:
		uint32_t mRendererId{};
		std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
		std::shared_ptr<IndexBuffer> mIndexBuffer;
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		void Bind() const override;
		void Unbind() const override;
		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;


		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return mVertexBuffers; }
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return mIndexBuffer; }
	};
}
