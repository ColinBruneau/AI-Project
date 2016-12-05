#include "stdafx.h"

#include "Graphics\SpriteRenderer.h"
#include "Core\GameManager.h"
#include "Graphics\ISprite.h"

namespace crea
{
	SpriteRenderer::SpriteRenderer()
	{
		m_pSprite = nullptr;
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
		return true;
	}
	
	bool SpriteRenderer::update()
	{
		return true;
	}
	
	bool SpriteRenderer::draw()
	{
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
