#pragma once
#include "Nocturnal/Renderer/VertexArray.h"
#include <memory>

namespace Nocturnal
{
	class OpenGLVertexArray : public VertexArray
	{
	private:
		uint32_t _rendererID{};
		std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
		std::shared_ptr<IndexBuffer> _indexBuffer;
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		void Bind() const override;
		void Unbind() const override;
		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;


		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return _vertexBuffers; }
		const std::shared_ptr<IndexBuffer>& GetIndexBuffers() const override { return _indexBuffer; }
	};
}
