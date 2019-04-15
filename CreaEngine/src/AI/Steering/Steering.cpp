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
		m_pTarget(nullptr), m_vSteeringDirection(0.f, 0.f)
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
	
	void Steering::addBehavior(Behavior* _Behavior, float _weight)
	{
		m_Behaviors.push_back(new PairFloatBehavior(_weight, _Behavior));
	};

	void Steering::removeBehavior(Behavior* _Behavior)
	{
		if (m_Behaviors.empty())
			return;

		auto a = std::remove_if(m_Behaviors.begin(), m_Behaviors.end(),
			[=](PairFloatBehavior* p) { return p->second == _Behavior; });

		if (a != m_Behaviors.end())
		{
			m_Behaviors.erase(a);
		}
	};

	void Steering::clearBehaviors()
	{
		for (int i = 0; i < (int)m_Behaviors.size(); i++)
		{
			PairFloatBehavior* p = m_Behaviors.back();
			delete(p);
			m_Behaviors.pop_back();
		}
		m_Behaviors.clear();
	};

	Vector2f Steering::steer()
	{
		Vector2f steeringDirection;
		for (int i = 0; i < (int)m_Behaviors.size(); i++)
		{
			PairFloatBehavior* t = m_Behaviors[i];
			Behavior* b = (Behavior*)t->second;
			Vector2f v = b->Update();
 			steeringDirection += (v * t->first);
		}
		return steeringDirection;
	}

	string Steering::asString()
	{
		stringstream stream;
		string szSteering("");
		Vector2f steeringDirection;
		for (int i = 0; i < (int)m_Behaviors.size(); i++)
		{
			PairFloatBehavior* t = m_Behaviors[i];
			Behavior* b = (Behavior*)t->second;
			szSteering += t->second->asString();
			szSteering += " ";
			stream << fixed << setprecision(1) << t->first;
			szSteering += stream.str();
		}
		return szSteering;
	}
	
	bool Steering::init()
	{
		m_pTarget = nullptr;

		return true;
	}

	bool Steering::update()
	{
		m_vSteeringDirection = steer();

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
