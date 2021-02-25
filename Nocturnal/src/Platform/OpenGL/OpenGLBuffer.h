#pragma once
#include "Nocturnal/Renderer/Buffer.h"

namespace Nocturnal
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t rendererID;
		BufferLayout bufferLayout;
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		void Bind() const override;
		void UnBind() const override;

		void SetLayout(const BufferLayout& layout) override { bufferLayout = layout; }
		const BufferLayout& GetLayout() const override { return bufferLayout; }
		
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t rendererID;
		uint32_t indicesCount;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;
		uint32_t GetCount() const override { return indicesCount; }
		
	};
}
