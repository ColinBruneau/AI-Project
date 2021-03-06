/***************************************************/
/* Nom:	SFMLShape.h
/* Description: SFMLShape
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _SFMLShape_H
#define _SFMLShape_H

#include "Graphics\Shape.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	class SFMLShape : public Shape
	{
	public:
		sf::Shape* m_pShape;

		SFMLShape() { m_pShape = nullptr; }
		virtual ~SFMLShape() { }

		virtual void draw()
		{
			sf::RenderWindow* pWin = SFMLFacade::Instance().m_pWindow;
			pWin->draw(*m_pShape);
		}
		
		virtual void setColor(Color* _pColor)
		{
			m_pShape->setFillColor(((SFMLColor*)_pColor)->getColor());
		}

		virtual void setOutlineColor(Color* _pColor)
		{
			m_pShape->setOutlineColor(((SFMLColor*)_pColor)->getColor());
		}

		virtual void setOutlineThickness(float _fPixels)
		{
			m_pShape->setOutlineThickness(_fPixels);
		}

		virtual void setPosition(float _x, float _y)
		{
			m_pShape->setPosition(_x, _y);
		}

		virtual void setRotation(float _angle)
		{
			m_pShape->setRotation(_angle);
		}

		virtual void setScale(float _x, float _y)
		{
			m_pShape->setScale(_x, _y);
		}

		virtual void setOrigin(float _x, float _y)
		{
			m_pShape->setOrigin(_x, _y);
		}

	};

	class SFMLRectangleShape : public SFMLShape
	{
	public:

		SFMLRectangleShape()
		{
			m_pShape = new sf::RectangleShape;
		}

		~SFMLRectangleShape()
		{
			delete m_pShape;
		}

		virtual void setSize(float _x, float _y)
		{
			((sf::RectangleShape*)m_pShape)->setSize(sf::Vector2f(_x, _y));
		}

	};

	class SFMLCircleShape : public SFMLShape
	{
	public:

		SFMLCircleShape()
		{
			m_pShape = new sf::CircleShape;
		}

		~SFMLCircleShape()
		{
			delete m_pShape;
		}

		virtual void setRadius(float _r)
		{
			((sf::CircleShape*)m_pShape)->setRadius(_r);
		}

	};
	
	class SFMLArrowShape : public SFMLShape
	{
	public:

		SFMLArrowShape()
		{
			sf::ConvexShape* pArrow = new sf::ConvexShape(3);
			pArrow->setPoint(0, sf::Vector2f(0.0f, 0.0f));
			pArrow->setPoint(1, sf::Vector2f(0.0f, 1.0f));
			pArrow->setPoint(2, sf::Vector2f(1.0f, 0.5f));
			m_pShape = pArrow;
		}

		~SFMLArrowShape()
		{
			delete m_pShape;
		}

		virtual void setSize(float _x, float _y)
		{
			m_pShape->setScale(sf::Vector2f(_x, _y));
		}
		
		virtual void setStartAndEnd(float _xStart, float _yStart, float _xEnd, float _yEnd)
		{
			float dx = _xEnd - _xStart;
			float dy = _yEnd - _yStart;
			Vector2f v(dx, dy);
			Vector2f right(1.0f, 0.f);
			float fAngle = right.angle(v)*180/3.14f;
			fAngle = dy > 0.f ? fAngle : -fAngle;
			sf::ConvexShape* pArrow = (sf::ConvexShape*) m_pShape;
			pArrow->setPosition(_xStart, _yStart);
			sf::Vector2f scale = pArrow->getScale();
			scale.x = v.length();
			pArrow->setScale(scale);
			pArrow->setOrigin(0.0f, 0.5f);
			pArrow->setRotation(fAngle);
		}

	};

	class SFMLLineShape : public SFMLShape
	{
	public:

		SFMLLineShape()
		{
			m_pShape = new sf::RectangleShape;
			setSize(1, 1);			
		}

		~SFMLLineShape()
		{
			delete m_pShape;
		}

		virtual void setSize(float _x, float _y)
		{
			((sf::RectangleShape*)m_pShape)->setSize(sf::Vector2f(_x, _y));
		}

		virtual void setStartAndEnd(float _xStart, float _yStart, float _xEnd, float _yEnd)
		{
			float dx = _xEnd - _xStart;
			float dy = _yEnd - _yStart;
			Vector2f v(dx, dy);
			Vector2f right(1.0f, 0.f);
			float fAngle = right.angle(v) * 180 / 3.14f;
			fAngle = dy > 0.f ? fAngle : -fAngle;
			sf::ConvexShape* pArrow = (sf::ConvexShape*) m_pShape;
			pArrow->setPosition(_xStart, _yStart);
			sf::Vector2f scale = pArrow->getScale();
			scale.x = v.length();
			pArrow->setScale(scale);
			pArrow->setRotation(fAngle);
		}

	};
	
	} // namespace crea

#endif // _SFMLShape_H