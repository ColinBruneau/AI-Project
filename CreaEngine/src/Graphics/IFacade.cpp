#include "stdafx.h"

#include "Graphics\IFacade.h"

namespace crea
{
	IFacade* IFacade::s_Instance = NULL;
	Plugin<IFacade> IFacade::s_Library;

} // namespace crea