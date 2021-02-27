#pragma once
#include "Nocturnal/Renderer/Buffer.h"

namespace Nocturnal
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t _RendererId;
		BufferLayout _BufferLayout;
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		void Bind() const override;
		void UnBind() const override;

		void SetLayout(const BufferLayout& layout) override { _BufferLayout = layout; }
		const BufferLayout& GetLayout() const override { return _BufferLayout; }
		
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t _RendererId;
		uint32_t _IndicesCount;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;
		uint32_t GetCount() const override { return _IndicesCount; }
		
	};
}
