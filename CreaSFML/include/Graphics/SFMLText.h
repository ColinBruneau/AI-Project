/***************************************************/
/* Nom:	SFMLText.h
/* Description: SFMLText
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLText_H
#define _SFMLText_H

#include "Graphics\Text.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLText : public Text
	{
	public:
		sf::Text* m_pText;

		SFMLText()
		{
			m_pText = new sf::Text;
		}

		virtual ~SFMLText()
		{
			delete m_pText;
		}

		virtual void draw()
		{
			sf::RenderWindow* pWin = SFMLFacade::Instance().m_pWindow;
			pWin->draw(*m_pText);
		}

		virtual void setFont(Font* _pFont)
		{
			SFMLFont* pFont = (SFMLFont*)_pFont;
			m_pText->setFont(pFont->m_font);
		}

		virtual void setColor(Color* _pColor)
		{
			SFMLColor* pColor = (SFMLColor*)_pColor;
			m_pText->setFillColor(pColor->getColor());
		}

		virtual void setCharacterSize(int _iSize)
		{
			m_pText->setCharacterSize(_iSize);
		}

		virtual void setString(string _szString)
		{
			m_pText->setString(_szString);
		}

		virtual void setPosition(float _x, float _y)
		{
			m_pText->setPosition(_x, _y);
		}

		virtual void setTextureRect(int _x, int _y, int _w, int _h)
		{
			m_pText->setPosition((float)_x, (float)_y);
			// CB: not handled with sfml...
			cerr << "Text rect not possible for now..." << endl;
		}
	};

} // namespace crea

#endif // _SFMLText_H