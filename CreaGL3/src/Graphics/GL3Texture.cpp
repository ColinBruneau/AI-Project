#include "stdafx.h"

#include "Graphics\GL3Texture.h"

namespace crea
{
	bool GL3Texture::m_flipVerticallyOnLoad = true;

	GL3Texture::GL3Texture()
		: m_texture(0),
		m_transparency(false),
		m_data(nullptr),
		m_width(0),
		m_height(0),
		m_nrChannels(0)
	{
		glGenTextures(1, &m_texture);
	}

	GL3Texture::~GL3Texture()
	{
		glDeleteTextures(1, &m_texture);
		if (m_data)
		{
			stbi_image_free(m_data);
		}
	}

	bool GL3Texture::loadFromFile(const string& _name)
	{
		// texture
		// -------
		glBindTexture(GL_TEXTURE_2D, m_texture);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		stbi_set_flip_vertically_on_load(m_flipVerticallyOnLoad); // tell stb_image.h to flip loaded texture's on the y-axis.
		m_data = stbi_load(_name.c_str(), &m_width, &m_height, &m_nrChannels, 0);
		if (!m_data)
		{
			std::cout << "Failed to load texture" << std::endl;
			return false;
		}
		m_name = _name;

		send();
		glGenerateMipmap(GL_TEXTURE_2D);

		return true;
	}

	void GL3Texture::send()
	{
		if (m_data)
		{
			GLenum format = GL_RGB;
			if (m_nrChannels == 1)
				format = GL_RED;
			else if (m_nrChannels == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);
		}
	}

	void GL3Texture::bind(unsigned int _channel)
	{
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0 + _channel);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		if (m_nrChannels == 4)
		{
			glEnable(GL_BLEND);// you enable blending function
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}

	void GL3Texture::unbind(unsigned int _channel)
	{
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0 + _channel);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


} // namespace crea
