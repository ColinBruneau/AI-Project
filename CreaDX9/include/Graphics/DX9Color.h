/***************************************************/
/* Nom:	DX9Color.h
/* Description: DX9Color
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Color_H
#define _DX9Color_H

#include "Graphics\IGraphics.h"

namespace crea
{

	class DX9Color : public IColor
	{
		D3DCOLOR m_color;
	public:
		D3DCOLOR getColor() { return m_color; }

		DX9Color()
		{
		}

		virtual ~DX9Color()
		{
		}

		virtual void setValues(int _r, int _g, int _b, int _a)
		{
			m_color = D3DCOLOR_RGBA(_r, _g, _b, _a);
		}
	};

} // namespace crea

#endif // _DX9Color_H