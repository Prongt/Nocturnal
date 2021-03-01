#pragma once
#include "Nocturnal/Renderer/Buffer.h"

namespace Nocturnal
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t mRendererId;
		BufferLayout mBufferLayout;
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		void Bind() const override;
		void UnBind() const override;

		void SetLayout(const BufferLayout& layout) override { mBufferLayout = layout; }
		const BufferLayout& GetLayout() const override { return mBufferLayout; }
		
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t mRendererId;
		uint32_t mIndicesCount;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;
		uint32_t GetCount() const override { return mIndicesCount; }
	};
}
