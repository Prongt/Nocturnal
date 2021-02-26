#pragma once
#include "Renderer.h"

namespace Nocturnal
{
	class Texture
	{
	private:
		uint32_t _RendererId;
		std::string _FilePath;
		unsigned char* _LocalBuffer;
		int _Width, _Height, _BitsPerPixel;
	public:
		Texture(std::string path);
		~Texture();
		void Bind(uint32_t slot = 0) const;
		void UnBind() const;

		int GetWidth() const { return _Width; }
		int GetHeight() const { return _Height; }
	};
}
