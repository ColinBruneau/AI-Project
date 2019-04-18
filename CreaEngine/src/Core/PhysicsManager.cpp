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

	void PhysicsManager::addStaticCollider(const string& _szName, Collider* _pCollider)
	{
		_pCollider->setName(_szName);
		m_StaticColliders[_szName] = _pCollider;
	}

	void PhysicsManager::addDynamicCollider(string& _szName, Collider* _pCollider)
	{
		_pCollider->setName(_szName);
		m_DynamicColliders[_szName] = _pCollider;
	}

	bool PhysicsManager::isColliding(Collider* _pCollider, bool _bWithStatic, bool _bWithDynamic, bool _bWithTrigger)
	{
		bool bIsColliding = false;

		// With static collisions
		if (_bWithStatic)
		{
			MapStringCollider::iterator it = m_StaticColliders.begin();
			while (it != m_StaticColliders.end())
			{
				Collider* pCollider = (Collider*)(it->second);
				if (_pCollider != pCollider && pCollider->isColliding(_pCollider, _bWithTrigger))
				{
					updateCollision(_pCollider, pCollider);
					bIsColliding = true;
				}
				++it;
			}
		}

		// With dynamic collisions
		if (_bWithDynamic)
		{
			MapStringCollider::iterator it = m_DynamicColliders.begin();
			while (it != m_DynamicColliders.end())
			{
				Collider* pCollider = (Collider*)(it->second);
				if (_pCollider != pCollider && pCollider->isColliding(_pCollider, _bWithTrigger))
				{
					updateCollision(_pCollider, pCollider);
					bIsColliding = true;
				}
				++it;
			}
		}

		return bIsColliding;
	}

	Collider* PhysicsManager::getStaticCollider(const string& _szName, bool _bCloned)
	{
		MapStringCollider::iterator it = m_StaticColliders.find(_szName);
		if (it == m_StaticColliders.end())
		{
			Collider* pCollider = Collider::loadFromFileJSON(DATAAGENTPATH + _szName); // Create a default Collider if none exist

			if (!pCollider)
			{
				cerr << "Unable to open Collider file" << endl;
				return nullptr;
			}

			m_StaticColliders[_szName] = pCollider;
			return pCollider;
		}
		else
		{
			if (_bCloned)
			{
				//return new Collider(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	Collider* PhysicsManager::getDynamicCollider(const string& _szName, bool _bCloned)
	{
		MapStringCollider::iterator it = m_DynamicColliders.find(_szName);
		if (it == m_DynamicColliders.end())
		{
			Collider* pCollider = Collider::loadFromFileJSON(DATAAGENTPATH + _szName); // Create a default Collider if none exist

			if (!pCollider)
			{
				cerr << "Unable to open Collider file" << endl;
				return nullptr;
			}
			pCollider->setName(_szName);
			m_DynamicColliders[_szName] = pCollider;
			return pCollider;
		}
		else
		{
			if (_bCloned)
			{
				//return new Collider(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	void PhysicsManager::setCurrentMap(Map* _pMap)
	{
		m_pCurrentMap = _pMap;
	}

	Map* PhysicsManager::getCurrentMap()
	{
		return m_pCurrentMap;
	}

	void PhysicsManager::callFunction(Collider* _pCollider, Collision2D* _pCollision, onCollisionFcn _fcn)
	{
		Entity* pEntity = _pCollider->getEntity();
		if (pEntity)
		{
			list<Script*> scripts;
			pEntity->getComponents<Script>(scripts);
			// and call callback function on all scripts
			for (list<Script*>::iterator it = scripts.begin(); it != scripts.end(); ++it)
			{
				Script* pScript = (Script*)*it;
				(pScript->*_fcn)(*_pCollision);
			}
		}
	}

	bool PhysicsManager::onEnterCollision(Collider* _pCollider, Collider* _pOtherCollider)
	{
		Collision2D* pCollision = new Collision2D();
		pCollision->m_pCollider = _pCollider;
		pCollision->m_pOtherCollider = _pOtherCollider;
		pCollision->m_bUpdated = true;
		m_Collisions2D.insert(MapColliderCollision2D::value_type(_pCollider, pCollision));

		// For 1st collider
		callFunction(_pCollider, pCollision, &Script::onCollisionEnter2D);
		// For 2nd collider
		callFunction(_pOtherCollider, pCollision, &Script::onCollisionEnter2D);

		return true;
	}

	bool PhysicsManager::onUpdateCollision(Collision2D* _pCollision)
	{
		// For 1st collider
		callFunction(_pCollision->m_pCollider, _pCollision, &Script::onCollisionStay2D);
		// For 2nd collider
		callFunction(_pCollision->m_pOtherCollider, _pCollision, &Script::onCollisionStay2D);

		return true;
	}

	bool PhysicsManager::onExitCollision(Collision2D* _pCollision)
	{
		// For 1st collider
		callFunction(_pCollision->m_pCollider, _pCollision, &Script::onCollisionExit2D);
		// For 2nd collider
		callFunction(_pCollision->m_pOtherCollider, _pCollision, &Script::onCollisionExit2D);

		return true;
	}

	bool PhysicsManager::updateCollision(Collider* _pCollider, Collider* _pOtherCollider)
	{
		// CB: todo: use of a multimap is not so nice (2 places to call new Collision2D) 
		MapColliderCollision2D::iterator it = m_Collisions2D.find(_pCollider);
		if (it == m_Collisions2D.end())
		{
			// no collision with this collider yet
			onEnterCollision(_pCollider, _pOtherCollider);
		}
		else
		{
			long count = m_Collisions2D.count(_pCollider);
			for (long i = 0; i < count; ++i, ++it)
			{
				Collision2D* pCollision = (Collision2D*)it->second;
				if (pCollision->m_pOtherCollider == _pOtherCollider)
				{
					onUpdateCollision(pCollision);
					pCollision->m_bUpdated = true;
					return true;
				}
			}
			// no collision with this pair yet...
			onEnterCollision(_pCollider, _pOtherCollider);
		}
		return true;
	}

	bool PhysicsManager::prepareCleanup()
	{
		long count = m_Collisions2D.size();
		MapColliderCollision2D::iterator it = m_Collisions2D.begin();
		for (long i = 0; i < count; ++i)
		{
			Collision2D* pCollision = (Collision2D*)it->second;
			pCollision->m_bUpdated = false;
			++it;
		}
		return true;
	}

	bool PhysicsManager::cleanupCollisions()
	{
		long count = m_Collisions2D.size();
		MapColliderCollision2D::iterator it = m_Collisions2D.begin();
		for (long i = 0; i < count; ++i)
		{
			Collision2D* pCollision = (Collision2D*)it->second;
			if (pCollision->m_bUpdated == true)
			{
				++it;
			}
			else
			{
				onExitCollision(pCollision);
				delete (*it).second;
				count--;
				it = m_Collisions2D.erase(it);
			}
		}
		return true;
	}

	bool PhysicsManager::clearCollisions()
	{
		MapColliderCollision2D::iterator it = m_Collisions2D.begin();
		while (it != m_Collisions2D.end()) {
			delete (it->second);
			it = m_Collisions2D.erase(it);
		}
		return true;
	}

	bool PhysicsManager::init()
	{
		return true;
	}

	bool PhysicsManager::update()
	{
		// Prepare cleanup
		prepareCleanup();

		// Check dynamic-static collisions
		MapStringCollider::iterator it = m_DynamicColliders.begin();
		while (it != m_DynamicColliders.end())
		{
			Collider* pCollider = (Collider*)(it->second);
			if (isColliding(pCollider, true, false, true)) // with static, not dynamic, with trigger!
			{
				// resolution

				//return true;
			}
			++it;
		}

		// Cleanup old collisions
		cleanupCollisions();

		return true;
	}

	bool PhysicsManager::draw()
	{
		return true;
	}

	void PhysicsManager::clear()
	{
		// Static
		MapStringCollider::iterator itStatic = m_StaticColliders.begin();
		while (itStatic != m_StaticColliders.end()) {
			delete (itStatic->second);
			itStatic = m_StaticColliders.erase(itStatic);
		}
		// Dynamic
		MapStringCollider::iterator itDynamic = m_DynamicColliders.begin();
		while (itDynamic != m_DynamicColliders.end()) {
			delete (itDynamic->second);
			itDynamic = m_DynamicColliders.erase(itDynamic);
		}

		m_pCurrentMap = nullptr;
	}

} // namespace crea
