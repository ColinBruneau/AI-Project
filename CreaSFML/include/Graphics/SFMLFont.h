/***************************************************/
/* Nom:	SFMLFont.h
/* Description: SFMLFont
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLFont_H
#define _SFMLFont_H

#include "Graphics\Font.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLFont : public Font
	{
	public:
		sf::Font m_font;

		virtual bool loadFromFile(const string& _file)
		{
			return m_font.loadFromFile(_file);
		}

		virtual void setFontSize(int _iSize)
		{
			// Todo: setFontSize SFML
		}
	};

} // namespace crea

#endif // _SFMLFont_H