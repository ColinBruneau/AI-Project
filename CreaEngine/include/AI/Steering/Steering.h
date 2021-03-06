/***************************************************/
/* Nom:	Steering.h
/* Description: Steering
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Steering_H_
#define __Steering_H_

#include "Core\Component.h"
#include "Core\Math.h"
#include "Core\GameManager.h"
#include "Graphics\Shape.h"

namespace crea
{
	// Predefinitions
	class GameManager;
	class Behavior;

	class CREAENGINE_API PairFloatBehavior : public pair<float, Behavior*>
	{
	public:
		PairFloatBehavior(float _f, Behavior* _p);
		~PairFloatBehavior();
	};

	class CREAENGINE_API Steering : public Component
	{
		Vector2f steer();

	protected:
		GameManager * m_pGM;

		// Collider
		Collider* m_pCollider;

		// Target
		Entity* m_pTarget;
		Vector2f m_vTargetOffset;

		std::vector<PairFloatBehavior*> m_behaviors; // All the behaviors and their weight associated

		Vector2f m_vSteeringDirection;

	public:
		Steering();
		virtual ~Steering();

		void setCollider(Collider* _pCollider);

		void setTarget(Entity* _pEntity) { m_pTarget = _pEntity; }
		Entity* getTarget() { return m_pTarget; }
		void setTargetOffset(Vector2f _vOffset) { m_vTargetOffset = _vOffset; }
		Vector2f getTargetOffset() { return m_vTargetOffset; }

		void addBehavior(Behavior* _behavior, float _weight);
		void removeBehavior(Behavior* _behavior);
		void clearBehaviors();

		Vector2f getSteeringDirection() { return m_vSteeringDirection; }

		string asString();

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();

		virtual Component* clone()
		{
			Steering* p = new Steering(*this);
			m_behaviors.clear();
			return p;
		} // CB: to do: keep behaviors (instanciate new PairFloatBehavior for each behavior)
	};

} // namespace crea

#endif
