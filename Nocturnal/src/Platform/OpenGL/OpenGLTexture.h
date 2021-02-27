#pragma once
#include "Nocturnal/Renderer/Texture.h"

namespace Nocturnal
{
	class OpenGLTexture : public Texture
	{
	private:
		uint32_t _RendererId;
		std::string _FilePath;
		unsigned char* _LocalBuffer;
		int _Width, _Height, _BitsPerPixel;
	public:
		OpenGLTexture(const std::string& path);
		virtual ~OpenGLTexture();
		void Bind(uint32_t slot) const override;
		void UnBind() const override;
		int GetWidth() const override { return _Width; }
		int GetHeight() const override { return _Height; }
	};
}
