/***************************************************/
/* Nom:	Transformable.h
/* Description: Transformable
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _Transformable_H
#define _Transformable_H

#include "Graphics\IGraphics.h"
#include "Core\ICore.h"

namespace crea
{
	class FloatRect;
	class Vector2f;

	class CREAENGINE_API Transform
	{
		Vector2f m_vPosition;
	public:

		Transform()
		{
		}

		~Transform()
		{
		}

		void move(Vector2f& _v) { m_vPosition += _v; }
		void setPosition(Vector2f& _v) { m_vPosition = _v; }
		Vector2f& getPosition() { return m_vPosition; }
		virtual FloatRect transformRect(const FloatRect&) { return FloatRect(); };
	};

	class CREAENGINE_API Transformable
	{
		Transform m_Transform;
	public:

		Transformable()
		{
		}

		~Transformable()
		{
		}

		Transform& getTransform() { return m_Transform; }
		void move(Vector2f& _v) { m_Transform.move(_v); }
		void setPosition(Vector2f& _v) { m_Transform.setPosition(_v); }
		Vector2f& getPosition() { return m_Transform.getPosition(); }
	};

} // namespace crea

#endif // _Transformable_H