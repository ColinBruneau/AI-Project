/***************************************************/
/* Nom:	SFMLFont.h
/* Description: SFMLFont
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLFont_H
#define _SFMLFont_H

#include "Graphics\IFont.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLFont : public IFont
	{
	public:
		sf::Font m_font;

		// Initialise le Font
		virtual bool loadFromFile(string _file)
		{
			return m_font.loadFromFile(_file);
		}
	};

} // namespace crea

#endif // _SFMLFont_H