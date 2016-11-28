/***************************************************/
/* Nom:	Collider.h
/* Description: Collider
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Collider_H_
#define __Collider_H_

#include "Core\Component.h"
#include "Core\ICore.h"

namespace crea
{
	enum EnumColliderType
	{
		Collider_Invalid = -1,
		Collider_Box = 0,
		Collider_Circle,
	};

	class CREAENGINE_API Collider : public Component
	{
		bool collisionBoxBox(Collider* _pCollider1, Collider* _pCollider2);
		bool collisionBoxCircle(Collider* _pCollider1, Collider* _pCollider2);
		bool collisionCircleCircle(Collider* _pCollider1, Collider* _pCollider2);

	protected:
		EnumColliderType m_eColliderType;
		void* m_pCollider;
		ISprite* m_pSprite;
		bool m_bIsColliding;

	public:
		Collider(EnumColliderType _eColliderType = Collider_Circle);
		virtual ~Collider();

		void* getCollider();

		bool isColliding(Collider* _pCollider);
		
		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();

	};

	class CREAENGINE_API BoxCollider
	{
		Vector2f m_vCenter;
		Vector2f m_vSize;

	public:
		BoxCollider();
		virtual ~BoxCollider();

		inline Vector2f& getCenter() { return m_vCenter; }
		inline Vector2f& getSize() { return m_vSize; }
		inline float getMinX() { return m_vCenter.getX(); }
		inline float getMinY() { return m_vCenter.getY(); }
		inline float getMaxX() { return m_vCenter.getX() + m_vSize.getX(); }
		inline float getMaxY() { return m_vCenter.getY() + m_vSize.getY(); }
		inline Vector2f getMin() { return Vector2f(getMinX(), getMinY()); }
		inline Vector2f getMax() { return Vector2f(getMaxX(), getMaxY()); }

	};

	class CREAENGINE_API CircleCollider
	{
		Vector2f m_vCenter;
		float m_fRadius;

	public:
		CircleCollider();
		virtual ~CircleCollider();

		inline Vector2f& getCenter() {	return m_vCenter; }
		inline float& getRadius() { return m_fRadius; }

	};

} // namespace crea

#endif
