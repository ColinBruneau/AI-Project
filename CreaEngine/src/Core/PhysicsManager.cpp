#include "stdafx.h"

#include "Core\PhysicsManager.h"
#include "Physics\Collider.h"

namespace crea
{
	PhysicsManager::PhysicsManager()
	{
		m_pCurrentMap = nullptr;
	}

	PhysicsManager::~PhysicsManager()
	{
		clear();
	}

	PhysicsManager* PhysicsManager::getSingleton()
	{
		static PhysicsManager instanceUnique;
		return
			&instanceUnique;
	}

	void PhysicsManager::addCollider(Collider* _pCollider)
	{
		m_Colliders.push_back(_pCollider);
	}

	bool PhysicsManager::isColliding(Collider* _pCollider)
	{
		VectorCollider::iterator it = m_Colliders.begin();
		while (it != m_Colliders.end())
		{
			Collider* pCollider = (Collider*)(*it);
			if (pCollider->isColliding(_pCollider))
			{
				return true;
			}
			++it;
		}
		return false;
	}

	void PhysicsManager::setCurrentMap(Map* _pMap)
	{
		m_pCurrentMap = _pMap;
	}

	Map* PhysicsManager::getCurrentMap()
	{
		return m_pCurrentMap;
	}

	bool PhysicsManager::init()
	{
		return true;
	}

	bool PhysicsManager::draw()
	{
		VectorCollider::iterator it = m_Colliders.begin();
		while (it != m_Colliders.end())
		{
			Collider* pCollider = (Collider*)(*it);
			pCollider->draw();
			++it;
		}
		return true;
	}

	void PhysicsManager::clear()
	{
		VectorCollider::iterator it = m_Colliders.begin();
		while (it != m_Colliders.end()) {
			delete (*it);
			it = m_Colliders.erase(it);
		}
		m_pCurrentMap = nullptr;
	}

} // namespace crea
