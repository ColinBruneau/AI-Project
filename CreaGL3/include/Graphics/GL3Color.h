/***************************************************/
/* Nom:	GL3Color.h
/* Description: GL3Color
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _GL3Color_H
#define _GL3Color_H

#include "Graphics\IGraphics.h"

namespace crea
{

	class GL3Color : public Color
	{
		int m_r; 
		int m_g;
		int m_b;
		int m_a;
		//D3DCOLOR m_color;
	public:
		//D3DCOLOR getColor() { return m_color; }

		GL3Color()
		{
		}

		virtual ~GL3Color()
		{
		}

		virtual void setValues(int _r, int _g, int _b, int _a)
		{
			m_r = _r;
			m_g = _g;
			m_b = _b;
			m_a = _a;
		}
	};

} // namespace crea

#endif // _GL3Color_H