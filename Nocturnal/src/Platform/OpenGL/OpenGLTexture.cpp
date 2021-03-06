#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLTexture.h"


#include "../../../vendor/stb_image/stb_image.h"
#include "glad/glad.h"

namespace Nocturnal
{
	OpenGLTexture::OpenGLTexture(const std::string& path)
		:mRendererId(0), mFilePath(path),
		mLocalBuffer(nullptr), mWidth(0),
		mHeight(0), mBitsPerPixel(0)
	{
		glGenTextures(1, &mRendererId);
		glBindTexture(GL_TEXTURE_2D, mRendererId);

		stbi_set_flip_vertically_on_load(1);
		mLocalBuffer = stbi_load(mFilePath.c_str(), &mWidth, &mHeight, &mBitsPerPixel, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		if (mLocalBuffer)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mLocalBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(mLocalBuffer);
		}
		else
		{
			NOC_CORE_ERROR(stbi_failure_reason());
			NOC_CORE_FATAL("Texture failed to load!");
		}
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &mRendererId);
	}

	void OpenGLTexture::Bind(const uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, mRendererId);
	}

	void OpenGLTexture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
