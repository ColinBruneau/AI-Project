/***************************************************/
/* Nom:	Steering.h
/* Description: Steering
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Steering_H_
#define __Steering_H_

#include "Core\Component.h"
#include "Core\ICore.h"
#include "Core\GameManager.h"
#include "Graphics\IGraphics.h"

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
	protected:
		GameManager* m_pGM;
		
		// Collider
		Collider* m_pCollider;

		// Target
		Entity* m_pTarget;

		// Locomotion
		float m_mass;
		Vector2f m_vVelocity;
		float m_maxForce;
		float m_maxSpeed;

		//last force to render
		Vector2f m_lastForce;
		Vector2f m_lastR;

		std::vector<PairFloatBehavior*> m_behaviors; // All the behaviors and their weight associated

		// debug lines
		ILine* m_pVelocityLine;
		ILine* m_pForceLine;

	public:
		Steering();
		virtual ~Steering();

		void setCollider(Collider* _pCollider);

		void setTarget(Entity* _pEntity) { m_pTarget = _pEntity; }
		Entity* getTarget() { return m_pTarget; }

		float getMass() { return m_mass; }
		Vector2f getVelocity() { return m_vVelocity; }
		float getMaxForce() { return m_maxForce; }
		float getMaxSpeed() { return m_maxSpeed; }
		Vector2f getLastForce() { return m_lastForce; }
		Vector2f getLastR() { return m_lastR; }

		void setMass(float _mass) { m_mass = _mass; }
		void setVelocity(Vector2f _velocity) { m_vVelocity = _velocity; }
		void setMaxForce(float _maxForce) { m_maxForce = _maxForce; }
		void setMaxSpeed(float _maxSpeed) { m_maxSpeed = _maxSpeed; }
		void setLastR(Vector2f _lastR) { m_lastR = _lastR; }

		Vector2f steer();
		void addBehavior(Behavior* _behavior, float _weight);
		void clearBehaviors();
						
		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();
	};

} // namespace crea

#endif
