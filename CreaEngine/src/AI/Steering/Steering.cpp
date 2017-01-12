#include "stdafx.h"

#include "AI\Steering\Steering.h"
#include "AI\Steering\Behavior.h"
#include "Physics\Collider.h"
#include "Core\PhysicsManager.h"

namespace crea
{
	PairFloatBehavior::PairFloatBehavior(float _f, Behavior* _p) : pair<float, Behavior*>(_f, _p) {}
	PairFloatBehavior::~PairFloatBehavior() { delete this->second; }

	Steering::Steering() :
		m_mass(1.0f),
		m_position(Vector2f(0.0f, 0.0f)),
		m_vVelocity(Vector2f(0.0f, 0.0f)),
		m_maxForce(100.0f),
		m_maxSpeed(100.0f),
		m_lastForce(Vector2f(0.0f, 0.0f)),
		m_lastR(Vector2f(1.0f, 0.0f)),
		m_pTarget(nullptr)
	{
		m_pGM = GameManager::getSingleton();
		m_pCollider = nullptr;
	}

	Steering::~Steering()
	{
		clearBehaviors();
	}

	void Steering::setCollider(Collider* _pCollider)
	{
		m_pCollider = _pCollider;
	}
	
	void Steering::addBehavior(Behavior* _behavior, float _weight)
	{
		m_behaviors.push_back(new PairFloatBehavior(_weight, _behavior));
	};

	void Steering::clearBehaviors()
	{
		for (int i = 0; i < (int)m_behaviors.size(); i++)
		{
			PairFloatBehavior* p = m_behaviors.back();
			delete(p);
			m_behaviors.pop_back();
		}
		m_behaviors.clear();
	};

	Vector2f Steering::steer()
	{
		Vector2f steeringDirection;
		for (int i = 0; i < (int)m_behaviors.size(); i++)
		{
			PairFloatBehavior* t = m_behaviors[i];
			Behavior* b = (Behavior*)t->second;
			steeringDirection += (t->second->Update() * t->first);
		}
		return steeringDirection;
	}
	
	bool Steering::init()
	{

		return true;
	}

	bool Steering::update()
	{
		Vector2f steeringDirection = steer();
		float frameTime = (float)TimeManager::getSingleton()->getFrameTime().asSeconds();

		if (!MathTools::zeroByEpsilon(steeringDirection.lengthSq()))
		{
			Vector2f steeringForce = MathTools::truncate(steeringDirection, m_maxForce);
			Vector2f acceleration = steeringForce / m_mass;
			m_vVelocity = MathTools::truncate(m_vVelocity + acceleration * frameTime, m_maxSpeed);

			m_lastForce = steeringForce;
		}
		else
		{
			m_lastForce = Vector2f(0.0f, 0.0f);
		}
		m_position += m_vVelocity * frameTime;
		m_pEntity->setPosition(m_position);

		return true;
	}

	bool Steering::draw()
	{
		return true;
	}

	bool Steering::quit()
	{
		return true;
	}
} // namespace crea
