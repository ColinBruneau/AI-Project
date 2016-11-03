/***************************************************/
/* Nom:	SFMLText.h
/* Description: SFMLText
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLText_H
#define _SFMLText_H

#include "Graphics\IText.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLText : public IText
	{
	public:
		sf::Text m_text;

		SFMLText()
		{
		}

		virtual ~SFMLText()
		{
		}

		virtual void draw()
		{
			sf::RenderWindow* pWin = SFMLFacade::Instance().m_pWindow;
			pWin->draw(this->m_text);
		}

		virtual void setFont(IFont* _pFont)
		{
			SFMLFont* pFont = (SFMLFont*)_pFont;
			m_text.setFont(pFont->m_font);
		}

		virtual void setColor(IColor* _pColor)
		{
			SFMLColor* pColor = (SFMLColor*)_pColor;
			m_text.setFillColor(pColor->m_color);
		}

		virtual void setCharacterSize(int _iSize)
		{
			m_text.setCharacterSize(_iSize);
		}

		virtual void setString(string _szString)
		{
			m_text.setString(_szString);
		}
	};

} // namespace crea

#endif // _SFMLText_H