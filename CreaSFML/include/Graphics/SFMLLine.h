/***************************************************/
/* Nom:	SFMLLine.h
/* Description: SFMLLine
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLLine_H
#define _SFMLLine_H

#include "Graphics\IGraphics.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLLine : public ILine
	{
	public:
		sf::Vertex m_line[2];

		virtual void draw()
		{
			sf::RenderWindow* pWin = SFMLFacade::Instance().m_pWindow;
			pWin->draw(m_line, 2, sf::Lines);
		}

		virtual void setLine(float _x1, float _y1, float _x2, float _y2)
		{
			m_line[0].position = sf::Vector2f(_x1, _y1);
			m_line[1].position = sf::Vector2f(_x2, _y2);
		}

		virtual void setColor(int _r, int _g, int _b, int _a)
		{
			m_line[0].color = m_line[1].color = sf::Color(_r, _g, _b, _a);
		}
	};

} // namespace crea

#endif // _SFMLLine_H