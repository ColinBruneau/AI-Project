/***************************************************/
/* Nom:	SFMLColor.h
/* Description: SFMLColor
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLColor_H
#define _SFMLColor_H

#include "Graphics\Color.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLColor : public Color
	{
	public:
		sf::Color getColor() { return sf::Color(m_r, m_g, m_b, m_a); }

		SFMLColor()
		{
		}

		virtual ~SFMLColor()
		{
		}
	};

} // namespace crea

#endif // _SFMLColor_H