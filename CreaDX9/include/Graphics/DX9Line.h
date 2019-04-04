/***************************************************/
/* Nom:	DX9Line.h
/* Description: DX9Line
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Line_H
#define _DX9Line_H

#include "Graphics\IGraphics.h"

namespace crea
{

	class DX9Line : public ILine
	{
	public:
		RECT m_rect;
		D3DCOLOR m_color;

		virtual void draw()
		{
		}

		virtual void setLine(float _x1, float _y1, float _x2, float _y2)
		{
			m_rect.left = (long)_x1;
			m_rect.top = (long)_y1;
			m_rect.bottom = (long)_y2;
			m_rect.right = (long)_x2;
		}

		virtual void setColor(int _r, int _g, int _b, int _a)
		{
			m_color = D3DCOLOR_RGBA(_r, _g, _b, _a);
		}
	};

} // namespace crea

#endif // _DX9Line_H