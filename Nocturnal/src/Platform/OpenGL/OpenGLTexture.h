#pragma once
#include "Nocturnal/Renderer/Texture.h"

namespace Nocturnal
{
	class OpenGLTexture : public Texture
	{
	private:
		uint32_t mRendererId;
		std::string mFilePath;
		unsigned char* mLocalBuffer;
		int mWidth;
		int mHeight;
		int mBitsPerPixel;
	public:
		OpenGLTexture(const std::string& path);
		virtual ~OpenGLTexture();
		void Bind(uint32_t slot) const override;
		void UnBind() const override;
		int GetWidth() const override { return mWidth; }
		int GetHeight() const override { return mHeight; }
	};
}
