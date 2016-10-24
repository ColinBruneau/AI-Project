/***************************************************/
/* Nom:	SFMLColor.h
/* Description: SFMLColor
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLColor_H
#define _SFMLColor_H

#include "Graphics\IGraphics.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLColor : public IColor
	{
	public:
		sf::Color m_color;

		SFMLColor()
		{
		}

		virtual ~SFMLColor()
		{
		}

		virtual void setValues(int _r, int _g, int _b, int _a)
		{
			m_color.r = _r;
			m_color.g = _g;
			m_color.b = _b;
			m_color.a = _a;
		}
	};

} // namespace crea

#endif // _SFMLColor_H