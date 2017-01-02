/***************************************************/
/* Nom:	DX9Text.h
/* Description: DX9Text
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Text_H
#define _DX9Text_H

#include "Graphics\IText.h"

namespace crea
{

	class DX9Text : public IText
	{
		LPD3DXFONT m_pFont;
		RECT *m_pRect;
		D3DCOLOR m_color;
		string m_szText;

	public:

		DX9Text()
		{
			//init rectangle
			m_pRect = nullptr;

			//init color
			m_color = D3DCOLOR_XRGB(255, 255, 255);

			//font
			m_pFont = nullptr;
		}

		virtual ~DX9Text()
		{
			SafeDelete(m_pRect);
			SafeRelease(m_pFont);
		}

		virtual void draw()
		{
			//sf::RenderWindow* pWin = DX9Facade::Instance().m_pWindow;
			//pWin->draw(this->m_text);

			assert(m_pFont); // A font must be set							  
			m_pFont->DrawText(NULL, m_szText.c_str(), -1, m_pRect, 0, m_color); // CB: pass a sprite as 1st param to improve speed x4
		}

		virtual void setFont(IFont* _pFont)
		{
			//DX9Font* pFont = (DX9Font*)_pFont;
			//m_text.setFont(pFont->m_font);
			DX9Font* pFont = (DX9Font*)_pFont;
			m_pFont = pFont->getFont();
		}

		virtual void setColor(IColor* _pColor)
		{
			//DX9Color* pColor = (DX9Color*)_pColor;
			//m_text.setFillColor(pColor->m_color);
			DX9Color* pColor = (DX9Color*)_pColor;
			m_color = pColor->getColor();
		}

		virtual void setCharacterSize(int _iSize)
		{
			//m_text.setCharacterSize(_iSize);

			// CB: not handled as it requires to recreate a font...
			cerr << "Text resizing not possible for now..." << endl;
		}

		virtual void setString(string _szString)
		{
			//m_text.setString(_szString);
			m_szText = _szString;
		}
	};

} // namespace crea

#endif // _DX9Text_H
