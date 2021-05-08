#include "NocturnalPrecompiledHeaders.h"
#include "OpenGLTexture.h"


#include "../../../vendor/stb_image/stb_image.h"
#include "glad/glad.h"

namespace Nocturnal
{
	OpenGLTexture::OpenGLTexture(const std::string& path)
		:mRendererId(0), mFilePath(path),
		mLocalBuffer(nullptr), mWidth(0),
		mHeight(0), mNumChannels(0)
	{
		glGenTextures(1, &mRendererId);
		glBindTexture(GL_TEXTURE_2D, mRendererId);

		stbi_set_flip_vertically_on_load(1);
		mLocalBuffer = stbi_load(mFilePath.c_str(), &mWidth, &mHeight, &mNumChannels, 0);

		if (mLocalBuffer)
		{
			GLenum textureFormat = GL_RGB;
		    if (mNumChannels == 1)
		        textureFormat = GL_RED;
		    else if (mNumChannels == 4)
		        textureFormat = GL_RGBA;
			
			glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, mWidth, mHeight, 0, textureFormat, GL_UNSIGNED_BYTE, mLocalBuffer);
			
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
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
