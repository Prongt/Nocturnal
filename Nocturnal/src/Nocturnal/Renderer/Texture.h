#pragma once
#include "Renderer.h"

namespace Nocturnal
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void UnBind() const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		static Texture* Create(const std::string& path);
	};
}
