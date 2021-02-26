#include "NocturnalPrecompiledHeaders.h"
#include "Texture.h"

#include <utility>

#include "glad/glad.h"
#include "../../vendor/stb_image.h"
namespace Nocturnal
{
	Texture::Texture(std::string path)
		:_RendererId(0), _FilePath(std::move(path)),
		_LocalBuffer(nullptr), _Width(0),
		_Height(0), _BitsPerPixel(0)
	{
		glGenTextures(1, &_RendererId);
		glBindTexture(GL_TEXTURE_2D, _RendererId);

		stbi_set_flip_vertically_on_load(1);
		_LocalBuffer = stbi_load(_FilePath.c_str(), &_Width, &_Height, &_BitsPerPixel, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		
		if (_LocalBuffer)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _Width, _Height, 0, GL_RGB, GL_UNSIGNED_BYTE, _LocalBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(_LocalBuffer);
		}else
		{
			NOC_CORE_ERROR(stbi_failure_reason());
			NOC_CORE_FATAL("Texture failed to load!");
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &_RendererId);
	}

	void Texture::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, _RendererId);
	}

	void Texture::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
