#pragma once
namespace Nocturnal
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer(){}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};
}
