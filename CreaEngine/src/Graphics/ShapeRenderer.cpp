#include "stdafx.h"

#include "Graphics\ShapeRenderer.h"

namespace crea
{
	ShapeRenderer::ShapeRenderer()
	{
		m_pShape = nullptr;
	}

	ShapeRenderer::~ShapeRenderer()
	{

	}

	bool ShapeRenderer::init()
	{
		return true;
	}
	
	bool ShapeRenderer::update()
	{
		return true;
	}
	
	bool ShapeRenderer::draw()
	{
		if (m_pShape)
		{
			m_pShape->draw();
		}

		return true;
	}
	
	bool ShapeRenderer::quit()
	{
		return true;
	}

} // namespace crea
