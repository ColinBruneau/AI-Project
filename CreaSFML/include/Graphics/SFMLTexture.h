/***************************************************/
/* Nom:	SFMLTexture.h
/* Description: SFMLTexture
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLTexture_H
#define _SFMLTexture_H

#include "Graphics\Texture.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLTexture : public ITexture
	{
	public:
		sf::Texture m_texture;

		SFMLTexture()
		{
		}

		~SFMLTexture()
		{
		}

		virtual bool loadFromFile(string _file)
		{
			return m_texture.loadFromFile(_file);
		}
	};

} // namespace crea

#endif // _SFMLTexture_H