/***************************************************/
/* Nom:	DX9Text.h
/* Description: DX9Text
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Text_H
#define _DX9Text_H

#include "Graphics\Text.h"

namespace crea
{

	class DX9Text : public IText
	{
		DX9Font* m_pDX9Font;
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
			m_pDX9Font = nullptr;
			m_pFont = nullptr;
		}

		virtual ~DX9Text()
		{
			SafeDelete(m_pRect);
			SafeRelease(m_pFont);
		}

		virtual void draw()
		{
			assert(m_pFont); // A font must be set	
			m_pFont->DrawText(NULL, m_szText.c_str(), -1, m_pRect, 0, m_color); // CB: pass a sprite as 1st param to improve speed x4
		}

		virtual void setFont(IFont* _pFont)
		{
			m_pDX9Font = (DX9Font*)_pFont;
			m_pFont = m_pDX9Font->getFont();
		}

		virtual void setColor(IColor* _pColor)
		{
			DX9Color* pColor = (DX9Color*)_pColor;
			m_color = pColor->getColor();
		}

		virtual void setCharacterSize(int _iSize)
		{
			assert(m_pDX9Font); // A font must be set as it requires reload of font...
			m_pDX9Font->setFontSize(_iSize);
		}

		virtual void setString(string _szString)
		{
			m_szText = _szString;
		}

		virtual void setPosition(float _x, float _y) 
		{
			if (!m_pRect)
				m_pRect = new RECT();

			m_pRect->left = (LONG)_x;
			m_pRect->top = (LONG)_y;
			m_pRect->bottom = (LONG)_y+100; 
			m_pRect->right = (LONG)_x+300;
			// CB: get size when only position is given (DrawText with CALCRECT)
			m_pFont->DrawText(NULL, m_szText.c_str(), -1, m_pRect, DT_CALCRECT, m_color);
		}

		virtual void setTextureRect(int _x, int _y, int _w, int _h) 
		{
			if (!m_pRect)
				m_pRect = new RECT();

			m_pRect->left = _x;
			m_pRect->top = _y;
			m_pRect->bottom = _y + _h;
			m_pRect->right = _x + _w;
		}

	};

} // namespace crea

#endif // _DX9Text_H
