/***************************************************/
/* Nom:	DX9Color.h
/* Description: DX9Color
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _DX9Color_H
#define _DX9Color_H

#include "Graphics\Color.h"

namespace crea
{

	class DX9Color : public Color
	{
	public:
		D3DCOLOR getColor() { return D3DCOLOR_RGBA(m_r, m_g, m_b, m_a); }

		DX9Color()
		{
		}

		virtual ~DX9Color()
		{
		}

	};

} // namespace crea

#endif // _DX9Color_H