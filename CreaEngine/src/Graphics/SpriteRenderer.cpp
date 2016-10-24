#include "stdafx.h"

#include "Graphics\SpriteRenderer.h"
#include "Core\GameManager.h"
#include "Graphics\ISprite.h"

namespace crea
{
	SpriteRenderer::SpriteRenderer()
	{
		m_pSprite = nullptr;
	}

	SpriteRenderer::~SpriteRenderer()
	{

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
			m_pSprite->draw();
		}

		return true;
	}
	
	bool SpriteRenderer::quit()
	{
		return true;
	}

} // namespace crea
