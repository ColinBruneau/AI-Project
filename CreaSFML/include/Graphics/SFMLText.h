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

		virtual void setPosition(float _x, float _y)
		{
			m_text.setPosition(_x, _y);
		}

		virtual void setTextureRect(int _x, int _y, int _w, int _h)
		{
			m_text.setPosition((float)_x, (float)_y);
			// CB: not handled with sfml...
			cerr << "Text rect not possible for now..." << endl;
		}
	};

} // namespace crea

#endif // _SFMLText_H