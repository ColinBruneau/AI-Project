#include "stdafx.h"

#include "Core\EntityManager.h"
#include "Data\Entity.h"
#include "Graphics\TextRenderer.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\MapRenderer.h"
#include "Graphics\Animator.h"
#include "Physics\CharacterController.h"
#include "Input\UserController.h"
#include "Physics\Collider.h"

namespace crea
{
	EntityManager::EntityManager()
	{
		m_pRoot = new Entity();
		m_pRoot->setName(string("root"));
	}

	EntityManager::~EntityManager()
	{
		delete m_pRoot;
		m_pRoot = nullptr;
	}

	EntityManager* EntityManager::getSingleton()
	{
		static EntityManager instanceUnique;
		return
			&instanceUnique;
	}

	void EntityManager::addEntity(Entity* _pEntity, Entity* _pParent)
	{
		if (_pParent)
		{
			_pParent->addChild(_pEntity);
		}
		else
		{
			m_pRoot->addChild(_pEntity);
		}
	}

	Entity* EntityManager::getEntity(string& _szName)
	{
		Entity* pEntity = nullptr;
		pEntity = m_pRoot->getEntity(_szName);
		if (!pEntity)
		{
			pEntity = new Entity();
			pEntity->setName(_szName);
		}
		return pEntity;
	}

	TextRenderer* EntityManager::getTextRenderer(string _szName, bool _bCloned)
	{
		MapStringTextRenderer::iterator it = m_pTextRenderers.find(_szName);
		if (it == m_pTextRenderers.end())
		{
			TextRenderer* pTextRenderer = new TextRenderer(); // Create a default TextRenderer if none exist
			m_pTextRenderers[_szName] = pTextRenderer;
			return pTextRenderer;
		}
		else
		{
			if (_bCloned)
			{
				//return new TextRenderer(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	SpriteRenderer* EntityManager::getSpriteRenderer(string _szName, bool _bCloned)
	{
		MapStringSpriteRenderer::iterator it = m_pSpriteRenderers.find(_szName);
		if (it == m_pSpriteRenderers.end())
		{
			SpriteRenderer* pSpriteRenderer = new SpriteRenderer(); // Create a default SpriteRenderer if none exist
			m_pSpriteRenderers[_szName] = pSpriteRenderer;
			return pSpriteRenderer;
		}
		else
		{
			if (_bCloned)
			{
				//return new SpriteRenderer(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	MapRenderer* EntityManager::getMapRenderer(string _szName, bool _bCloned)
	{
		MapStringMapRenderer::iterator it = m_pMapRenderers.find(_szName);
		if (it == m_pMapRenderers.end())
		{
			MapRenderer* pMapRenderer = new MapRenderer(); // Create a default MapRenderer if none exist
			m_pMapRenderers[_szName] = pMapRenderer;
			return pMapRenderer;
		}
		else
		{
			if (_bCloned)
			{
				//return new MapRenderer(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	Animator* EntityManager::getAnimator(string _szName, bool _bCloned)
	{
		MapStringAnimator::iterator it = m_pAnimators.find(_szName);
		if (it == m_pAnimators.end())
		{
			Animator* pAnimator = new Animator(); // Create a default Animator if none exist
			m_pAnimators[_szName] = pAnimator;
			return pAnimator;
		}
		else
		{
			if (_bCloned)
			{
				//return new Animator(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	CharacterController* EntityManager::getCharacterController(string _szName, bool _bCloned)
	{
		MapStringCharacterController::iterator it = m_pCharacterControllers.find(_szName);
		if (it == m_pCharacterControllers.end())
		{
			CharacterController* pCharacterController = new CharacterController(); // Create a default CharacterController if none exist
			m_pCharacterControllers[_szName] = pCharacterController;
			return pCharacterController;
		}
		else
		{
			if (_bCloned)
			{
				//return new CharacterController(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	UserController* EntityManager::getUserController(string _szName, bool _bCloned)
	{
		MapStringUserController::iterator it = m_pUserControllers.find(_szName);
		if (it == m_pUserControllers.end())
		{
			UserController* pUserController = new UserController(); // Create a default UserController if none exist
			m_pUserControllers[_szName] = pUserController;
			return pUserController;
		}
		else
		{
			if (_bCloned)
			{
				//return new UserController(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
	}

	Collider* EntityManager::getCollider(string _szName, bool _bCloned)
	{
		MapStringCollider::iterator it = m_pColliders.find(_szName);
		if (it == m_pColliders.end())
		{
			Collider* pCollider = new Collider(); // Create a default Collider if none exist
			m_pColliders[_szName] = pCollider;
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

	bool EntityManager::init()
	{
		return m_pRoot->init();
	}

	bool EntityManager::update()
	{
		return m_pRoot->update();
	}

	bool EntityManager::draw()
	{		
		return m_pRoot->draw();
	}

	void EntityManager::clear()
	{
		MapStringTextRenderer::iterator itTextRenderer = m_pTextRenderers.begin();
		while (itTextRenderer != m_pTextRenderers.end()) {
			delete (*itTextRenderer).second;
			itTextRenderer = m_pTextRenderers.erase(itTextRenderer);
		}

		MapStringSpriteRenderer::iterator itSpriteRenderer = m_pSpriteRenderers.begin();
		while (itSpriteRenderer != m_pSpriteRenderers.end()) {
			delete (*itSpriteRenderer).second;
			itSpriteRenderer = m_pSpriteRenderers.erase(itSpriteRenderer);
		}

		MapStringMapRenderer::iterator itMapRenderer = m_pMapRenderers.begin();
		while (itMapRenderer != m_pMapRenderers.end()) {
			delete (*itMapRenderer).second;
			itMapRenderer = m_pMapRenderers.erase(itMapRenderer);
		}

		MapStringAnimator::iterator itAnimator = m_pAnimators.begin();
		while (itAnimator != m_pAnimators.end()) {
			delete (*itAnimator).second;
			itAnimator = m_pAnimators.erase(itAnimator);
		}

		MapStringCharacterController::iterator itCharacterController = m_pCharacterControllers.begin();
		while (itCharacterController != m_pCharacterControllers.end()) {
			delete (*itCharacterController).second;
			itCharacterController = m_pCharacterControllers.erase(itCharacterController);
		}

		MapStringUserController::iterator itUserController = m_pUserControllers.begin();
		while (itUserController != m_pUserControllers.end()) {
			delete (*itUserController).second;
			itUserController = m_pUserControllers.erase(itUserController);
		}

		MapStringCollider::iterator itCollider = m_pColliders.begin();
		while (itCollider != m_pColliders.end()) {
			delete (*itCollider).second;
			itCollider = m_pColliders.erase(itCollider);
		}

		if (m_pRoot)
		{
			m_pRoot->clear();
		}
	}
} // namespace crea
