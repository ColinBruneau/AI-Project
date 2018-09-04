/***************************************************/
/* Nom:	GL3Text.h
/* Description: GL3Text
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _GL3Text_H
#define _GL3Text_H

#include "Graphics\Text.h"

namespace crea
{

	class GL3Text : public Text
	{
		//LPD3DXFONT 
		void* m_pFont;
		RECT *m_pRect;
		GL3Color* m_color;
		string m_szText;

	public:

		GL3Text()
		{
			//init rectangle
			m_pRect = nullptr;

			//init color
			m_color->setValues(255, 255, 255, 100);

			//font
			m_pFont = nullptr;
		}

		virtual ~GL3Text()
		{
			SafeDelete(m_pRect);
			SafeDelete(m_pFont);
		}

		virtual void draw()
		{
			assert(m_pFont); // A font must be set	
			//m_pFont->DrawText(NULL, m_szText.c_str(), -1, m_pRect, 0, m_color); // CB: pass a sprite as 1st param to improve speed x4
		}

		virtual void setFont(IFont* _pFont)
		{
			GL3Font* pFont = (GL3Font*)_pFont;
			m_pFont = pFont->getFont();
		}

		virtual void setColor(Color* _pColor)
		{
			m_color = (GL3Color*)_pColor;
		}

		virtual void setCharacterSize(int _iSize)
		{
			// CB: not handled as it requires to recreate a font...
			cerr << "Text resizing not possible for now..." << endl;
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
			//m_pFont->DrawText(NULL, m_szText.c_str(), -1, m_pRect, DT_CALCRECT, m_color);
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

#endif // _GL3Text_H
