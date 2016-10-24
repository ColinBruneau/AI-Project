#include "stdafx.h"

#include "Graphics\IRenderer.h"

namespace crea
{
	IRenderer* IRenderer::s_Instance = NULL;
	Plugin<IRenderer> IRenderer::s_Library;

} // namespace crea