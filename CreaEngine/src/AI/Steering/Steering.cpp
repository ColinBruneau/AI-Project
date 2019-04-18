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

	void Steering::addBehavior(Behavior* _behavior, float _weight)
	{
		m_behaviors.push_back(new PairFloatBehavior(_weight, _behavior));
	};

	void Steering::removeBehavior(Behavior* _behavior)
	{
		if (m_behaviors.empty())
			return;

		auto a = std::remove_if(m_behaviors.begin(), m_behaviors.end(),
			[=](PairFloatBehavior* p) { return p->second == _behavior; });

		m_behaviors.erase(a);
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
		for (int i = 0; i < (int)m_behaviors.size(); i++)
		{
			PairFloatBehavior* t = m_behaviors[i];
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
