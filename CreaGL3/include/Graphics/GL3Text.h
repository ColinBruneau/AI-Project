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
		GL3Font* m_pFont;
		RECT *m_pRect;
		GL3Color m_color;
		string m_szText; 
		float m_fSize;

	public:

		GL3Text()
		{
			//init rectangle
			m_pRect = new RECT();

			//init color
			m_color.setValues(255, 255, 255, 100);

			//font
			m_pFont = nullptr;

			m_fSize = 20.f;
		}

		virtual ~GL3Text()
		{
			SafeDelete(m_pRect);
			// SafeDelete(m_pFont); // Font not allocated in GL3Text
		}

		virtual void draw()
		{
			assert(m_pFont); // A font must be set	
			m_pFont->renderText(m_szText.c_str(), (float)m_pRect->left, (float)m_pRect->top, m_fSize, glm::vec3(m_color.getR(), m_color.getG(), m_color.getB()));
		}

		virtual void setFont(Font* _pFont)
		{
			m_pFont = (GL3Font*)_pFont;
		}

		virtual void setColor(Color* _pColor)
		{
			m_color.setValues(_pColor->m_r, _pColor->m_g, _pColor->m_b, _pColor->m_a);
		}

		virtual void setCharacterSize(int _iSize)
		{
			m_fSize = (float)_iSize;
		}

		virtual void setString(string _szString)
		{
			m_szText = _szString;
		}

		virtual void setPosition(float _x, float _y) 
		{
			m_pRect->left = (LONG)_x;
			m_pRect->top = (LONG)_y;
			m_pRect->bottom = (LONG)_y+100; // todo: size is not handled for text in GL3
			m_pRect->right = (LONG)_x+300;
		}

		virtual void setTextureRect(int _x, int _y, int _w, int _h) 
		{
			m_pRect->left = _x;
			m_pRect->top = _y;
			m_pRect->bottom = _y + _h;
			m_pRect->right = _x + _w;
		}

	};

} // namespace crea

#endif // _GL3Text_H
