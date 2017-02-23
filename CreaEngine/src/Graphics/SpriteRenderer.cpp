#include "stdafx.h"

#include "Graphics\SpriteRenderer.h"
#include "Core\GameManager.h"
#include "Graphics\ISprite.h"

namespace crea
{
	SpriteRenderer::SpriteRenderer()
	{
		m_pSprite = nullptr;
		m_pSelectionSprite = nullptr;
		m_pTextureRect = nullptr;
	}

	SpriteRenderer::~SpriteRenderer()
	{
		if (m_pTextureRect)
		{
			delete m_pTextureRect;
		}
	}

	bool SpriteRenderer::init()
	{
		// Selection
		m_pSelectionSprite = crea::GameManager::getSingleton()->getSprite("debug/selection");
		m_pSelectionSprite->setTexture(crea::GameManager::getSingleton()->getTexture("debug/selection.png"));

		return true;
	}
	
	bool SpriteRenderer::update()
	{
		return true;
	}
	
	bool SpriteRenderer::draw()
	{
		// Selection
		if (m_pSelectionSprite && getEntity()->getSelected())
		{
			Vector2f vPos = getEntity()->getPosition();
			m_pSelectionSprite->setPosition(vPos.getX(), vPos.getY());
			m_pSelectionSprite->setOrigin(64, 64);
			//Vector2f vSize = m_pSprite->getSize();
			//m_pSelectionSprite->setScale(ONEOVER128*vSize.getX(), ONEOVER128*vSize.getY());
			m_pSelectionSprite->setScale(ONEOVER128*36, ONEOVER128*36);
			m_pSelectionSprite->draw();
		}

		if (m_pSprite)
		{
			Vector2f vPos = getEntity()->getPosition();
			m_pSprite->setPosition(vPos.getX(), vPos.getY());
			if (m_pTextureRect)
			{
				m_pSprite->setTextureRect(m_pTextureRect->getLeft(), m_pTextureRect->getTop(), 
					m_pTextureRect->getWidth(), m_pTextureRect->getHeight());
			}
			m_pSprite->draw();
		}

		return true;
	}
	
	bool SpriteRenderer::quit()
	{
		return true;
	}

} // namespace crea
