#include "stdafx.h"

#include "Graphics\TextRenderer.h"
#include "Core\GameManager.h"
#include "Graphics\IText.h"

namespace crea
{
	TextRenderer::TextRenderer()
	{
		m_pText = nullptr;
	}
	
	TextRenderer::~TextRenderer()
	{

	}

	bool TextRenderer::init()
	{
		return true;
	}
	
	bool TextRenderer::update()
	{
		return true;
	}
	
	bool TextRenderer::draw()
	{
		if (m_pText)
		{
			Vector2f vPos = getEntity()->getPosition();
			m_pText->setPosition(vPos.getX(), vPos.getY());
			if (m_pTextureRect)
			{
				m_pText->setTextureRect(m_pTextureRect->getLeft(), m_pTextureRect->getTop(),
					m_pTextureRect->getWidth(), m_pTextureRect->getHeight());
			}
			m_pText->draw();
		}

		return true;
	}
	
	bool TextRenderer::quit()
	{
		return true;
	}

} // namespace crea
