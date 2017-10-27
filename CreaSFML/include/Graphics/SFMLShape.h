/***************************************************/
/* Nom:	SFMLShape.h
/* Description: SFMLShape
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLShape_H
#define _SFMLShape_H

#include "Graphics\IShape.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLShape : public IShape
	{
	public:
		sf::Shape* m_pShape;

		SFMLShape() { m_pShape = nullptr; }
		virtual ~SFMLShape() { }

		virtual void draw()
		{
			sf::RenderWindow* pWin = SFMLFacade::Instance().m_pWindow;
			pWin->draw(*this->m_pShape);
		}
		
		virtual void setColor(IColor* _pColor)
		{
			m_pShape->setFillColor(((SFMLColor*)_pColor)->m_color);
		}

		virtual void setOutlineColor(IColor* _pColor)
		{
			m_pShape->setOutlineColor(((SFMLColor*)_pColor)->m_color);
		}

		virtual void setOutlineThickness(float _fPixels)
		{
			m_pShape->setOutlineThickness(_fPixels);
		}

		virtual void setPosition(float _x, float _y)
		{
			m_pShape->setPosition(_x, _y);
		}

	};

	class SFMLRectangleShape : public IRectangleShape
	{
	public:
		sf::Shape* m_pShape;

		SFMLRectangleShape() { m_pShape = new sf::RectangleShape; }
		virtual ~SFMLRectangleShape() { delete m_pShape; }

		virtual void draw()
		{
			sf::RenderWindow* pWin = SFMLFacade::Instance().m_pWindow;
			pWin->draw(*this->m_pShape);
		}

		virtual void setColor(IColor* _pColor)
		{
			m_pShape->setFillColor(((SFMLColor*)_pColor)->m_color);
		}

		virtual void setOutlineColor(IColor* _pColor)
		{
			m_pShape->setOutlineColor(((SFMLColor*)_pColor)->m_color);
		}

		virtual void setOutlineThickness(float _fPixels)
		{
			m_pShape->setOutlineThickness(_fPixels);
		}

		virtual void setPosition(float _x, float _y)
		{
			m_pShape->setPosition(_x, _y);
		}

		virtual void setSize(float _x, float _y)
		{
			((sf::RectangleShape*)m_pShape)->setSize(sf::Vector2f(_x, _y));
		}

	};
} // namespace crea

#endif // _SFMLShape_H