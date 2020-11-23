/***************************************************/
/* Nom:	GL3Color.h
/* Description: GL3Color
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _GL3Color_H
#define _GL3Color_H

#include "Graphics\Color.h"

namespace crea
{
	class GL3Color : public Color
	{
		unsigned char m_r;
		unsigned char m_g;
		unsigned char m_b;
		unsigned char m_a;
	public:
		GL3Color(
			unsigned char _r,
			unsigned char _g,
			unsigned char _b,
			unsigned char _a) 
		{
			m_r = _r;
			m_g = _g;
			m_b = _b;
			m_a = _a;
		}

		float getR() const { return m_r * ONEOVER255; }
		float getG() const { return m_g * ONEOVER255; }
		float getB() const { return m_b * ONEOVER255; }
		float getA() const { return m_a * ONEOVER255; }

		GL3Color()
		{
		}

		virtual ~GL3Color()
		{
		}

		virtual void setValues(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
		{
			m_r = _r;
			m_g = _g;
			m_b = _b;
			m_a = _a;
		}
	};

} // namespace crea

#endif // _GL3Color_H