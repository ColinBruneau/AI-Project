#include "stdafx.h"

#include "Graphics\Shape.h"

#include <SFML/Graphics.hpp>

namespace crea
{

	Shape::Shape()
	{
		m_pShape = nullptr;
	}

	Shape::~Shape()
	{
	}

	void Shape::draw()
	{
		GameManager::getSingleton()->getWindow()->draw(*m_pShape);
	}

	void Shape::setColor(Color* _pColor)
	{
		m_pShape->setFillColor(*_pColor->m_pColor);
	}

	void Shape::setOutlineColor(Color* _pColor)
	{
		m_pShape->setOutlineColor(*_pColor->m_pColor);
	}

	void Shape::setOutlineThickness(float _fPixels)
	{
		m_pShape->setOutlineThickness(_fPixels);
	}

	void Shape::setPosition(float _x, float _y)
	{
		m_pShape->setPosition(_x, _y);
	}

	// RectangleShape
	RectangleShape::RectangleShape()
	{
		m_pShape = new sf::RectangleShape;
	}

	RectangleShape::~RectangleShape()
	{
		delete m_pShape;
	}

	void RectangleShape::setSize(float _x, float _y)
	{
		((sf::RectangleShape*)m_pShape)->setSize(sf::Vector2f(_x, _y));
	}
} // namespace crea
