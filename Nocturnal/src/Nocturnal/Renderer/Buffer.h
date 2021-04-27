#pragma once
#include <utility>

#include "stdint.h"
namespace Nocturnal
{
	enum class ShaderType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};
	
	static uint32_t ShaderTypeSize(const ShaderType type)
	{
		switch (type)
		{
		case ShaderType::Int:
		case ShaderType::Float:		return 4;

		case ShaderType::Int2:
		case ShaderType::Float2:	return 8;

		case ShaderType::Int3:
		case ShaderType::Float3:	return 12;
			
		case ShaderType::Int4:
		case ShaderType::Float4:	return 16;
		
		case ShaderType::Mat3:		return 4 * 3 * 3;
		case ShaderType::Mat4:		return 4 * 4 * 4;
		case ShaderType::Bool:		return sizeof(bool);
		case ShaderType::None:		return 0;
		}
		NOC_CORE_ASSERT(false, "Shader Type not valid!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferElement() = default;
		BufferElement(const ShaderType type, std::string name, const bool normalized = false)
			: Name(std::move(name)), Type(type), Offset(0), Size(ShaderTypeSize(type)), Normalized(normalized) {}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderType::Int:
			case ShaderType::Float:		return 1;
				
			case ShaderType::Int2:
			case ShaderType::Float2:	return 2;
				
			case ShaderType::Int3:
			case ShaderType::Float3:	return 3;
				
			case ShaderType::Int4:
			case ShaderType::Float4:	return 4;
			
			
			case ShaderType::Mat3:		return 3 * 3;
			case ShaderType::Mat4:		return 4 * 4;
			case ShaderType::Bool:		return 1;
			case ShaderType::None:		return 0;
			}
			NOC_CORE_ASSERT(false, "Shader Type not valid!");
			return 0;
		}
	};
	
	class BufferLayout
	{
	private:
		std::vector<BufferElement> mBufferElements;
		uint32_t mStride = 0;
		
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			mStride = 0;
			for (auto& element : mBufferElements)
			{
				element.Offset = offset;
				offset += element.Size;
				mStride += element.Size;
			}
		}
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:	mBufferElements(elements)
		{
			CalculateOffsetsAndStride();
		}

		const std::vector<BufferElement>& GetElements() const { return mBufferElements; }
		uint32_t GetStride() const { return mStride; }

		std::vector<BufferElement>::iterator begin() { return mBufferElements.begin(); }
		std::vector<BufferElement>::iterator end() { return mBufferElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return mBufferElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return mBufferElements.end(); }
	};
	
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};
}