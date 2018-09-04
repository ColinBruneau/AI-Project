#include "stdafx.h"

#include "Graphics\TextRenderer.h"
#include "Core\GameManager.h"

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
			m_pText->draw();
		}

		return true;
	}
	
	bool TextRenderer::quit()
	{
		return true;
	}

} // namespace crea
