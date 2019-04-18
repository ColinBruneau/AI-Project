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

	class SFMLTexture : public Texture
	{
	public:
		sf::Texture* m_pTexture;

		SFMLTexture()
		{
			m_pTexture = new sf::Texture;
		}

		~SFMLTexture()
		{
			delete m_pTexture;
		}

		virtual bool loadFromFile(const string& _file)
		{
			return m_pTexture->loadFromFile(_file);
		}
	};

} // namespace crea

#endif // _SFMLTexture_H