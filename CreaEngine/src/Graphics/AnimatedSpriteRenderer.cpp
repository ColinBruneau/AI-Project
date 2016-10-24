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
			m_pSprite->setTexture(m_pAnimatedSprite->getTexture());

			IntRect rect = m_pAnimatedSprite->getFrame();
			m_pSprite->setTextureRect(	(int)rect.getLeft(), 
										(int)rect.getTop(), 
										(int)rect.getWidth(), 
										(int)rect.getHeight());

			Vector2f _v;
			m_pAnimatedSprite->getPosition(_v);
			m_pSprite->setPosition(_v.getX(), _v.getY());
			m_pSprite->draw();
		}

		return true;
	}
	
	bool AnimatedSpriteRenderer::quit()
	{
		return true;
	}

} // namespace crea
