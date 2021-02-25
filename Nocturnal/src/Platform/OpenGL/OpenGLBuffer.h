#pragma once
#include "Nocturnal/Renderer/Buffer.h"

namespace Nocturnal
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t rendererID;
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		void Bind() const override;
		void UnBind() const override;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t rendererID;
		uint32_t indicesCount;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;
		virtual uint32_t GetCount() const { return indicesCount; }
		
	};
}
