/***************************************************/
/* Nom:	CellsScriptFactory.h
/* Description: CellsScriptFactory
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __CellsScriptFactory_H_
#define __CellsScriptFactory_H_

#include "Core\Script.h"
#include "CharacterController.h"
#include "UserController.h"

namespace crea
{
	class CellsScriptFactory : public ScriptFactory
	{
		virtual Script* create(string& _szName) 
		{ 
			if (_szName == "CharacterController")
			{
				return new CharacterController;
			}
			else if (_szName == "UserController")
			{
				return new UserController;
			}
			return nullptr;
		}
	};
} // namespace crea

#endif
