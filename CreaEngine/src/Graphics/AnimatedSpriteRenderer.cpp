#include "stdafx.h"

#include "Graphics\AnimatedSpriteRenderer.h"
#include "Core\GameManager.h"
#include "Graphics\ISprite.h"

namespace crea
{
	AnimatedSpriteRenderer::AnimatedSpriteRenderer(string _szName)
	{
		m_pAnimatedSprite = nullptr;
		m_pSprite = crea::GameManager::getSingleton()->getSprite(_szName);
	}

	AnimatedSpriteRenderer::~AnimatedSpriteRenderer()
	{

	}

	bool AnimatedSpriteRenderer::init()
	{
		return true;
	}
	
	bool AnimatedSpriteRenderer::update()
	{
		return true;
	}
	
	bool AnimatedSpriteRenderer::draw()
	{
		if (m_pAnimatedSprite)
		{
			ITexture* pTexture = m_pAnimatedSprite->getTexture();
			if (pTexture)
			{
				m_pSprite->setTexture(pTexture);

				IntRect rect = m_pAnimatedSprite->getFrame();
				float fFlipH = (rect.getWidth() < 0) ? -1.0f : 1.0f;// width < 0 means flipH
				float fFlipV = (rect.getHeight() < 0) ? -1.0f : 1.0f;// height < 0 means flipV

				m_pSprite->setTextureRect((int)rect.getLeft(),
					(int)rect.getTop(),
					(int)rect.getWidth()*fFlipH,	
					(int)rect.getHeight()*fFlipV);

				m_pSprite->setScale(fFlipH, fFlipV);

				m_pSprite->setOrigin(rect.getWidth()*0.5f*fFlipH, rect.getHeight()*0.5f*fFlipV);
				
				Vector2f _v;
				m_pAnimatedSprite->getPosition(_v);
				m_pSprite->setPosition(_v.getX(), _v.getY());
				m_pSprite->draw();
			}
		}

		return true;
	}
	
	bool AnimatedSpriteRenderer::quit()
	{
		return true;
	}

} // namespace crea
