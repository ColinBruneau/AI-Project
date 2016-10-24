#include "stdafx.h"

#include "Core\EntityManager.h"
#include "Data\Entity.h"
#include "Graphics\TextRenderer.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\MapRenderer.h"
#include "Graphics\AnimatedSpriteRenderer.h"

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

	AnimatedSpriteRenderer* EntityManager::getAnimatedSpriteRenderer(string _szName, bool _bCloned)
	{
		MapStringAnimatedSpriteRenderer::iterator it = m_pAnimatedSpriteRenderers.find(_szName);
		if (it == m_pAnimatedSpriteRenderers.end())
		{
			AnimatedSpriteRenderer* pAnimatedSpriteRenderer = new AnimatedSpriteRenderer(_szName); // Create a default AnimatedSpriteRenderer if none exist
			m_pAnimatedSpriteRenderers[_szName] = pAnimatedSpriteRenderer;
			return pAnimatedSpriteRenderer;
		}
		else
		{
			if (_bCloned)
			{
				//return new AnimatedSpriteRenderer(it->second); // CB is it useful to clone?
			}
			else
			{
				return it->second;
			}
		}
		return nullptr;
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

		MapStringAnimatedSpriteRenderer::iterator itAnimatedSpriteRenderer = m_pAnimatedSpriteRenderers.begin();
		while (itAnimatedSpriteRenderer != m_pAnimatedSpriteRenderers.end()) {
			delete (*itAnimatedSpriteRenderer).second;
			itAnimatedSpriteRenderer = m_pAnimatedSpriteRenderers.erase(itAnimatedSpriteRenderer);
		}

		if (m_pRoot)
		{
			m_pRoot->clear();
		}
	}
} // namespace crea
