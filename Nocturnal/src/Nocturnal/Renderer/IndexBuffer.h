#pragma once
namespace Nocturnal
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static IndexBuffer* Create(uint32_t indices, uint32_t size);
	};
}