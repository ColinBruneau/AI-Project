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
#include "FSMPeon.h"
#include "Scripts\FSMSteeringPeon.h"
#include "FSMBalista.h"
#include "Scripts\FSMHQ.h"


class CellsScriptFactory : public ScriptFactory
{
	virtual Script* create(const string& _szName)
	{
		if (_szName == "CharacterController")
		{
			return new CharacterController;
		}
		else if (_szName == "CharacterControllerBalista")
		{
			return new CharacterController;
		}
		else if (_szName == "CharacterControllerSteeringPeon")
		{
			return new CharacterController;
		}
		else if (_szName == "UserController")
		{
			return new UserController;
		}
		else if (_szName == "FSMPeon")
		{
			return new FSMPeon;
		}
		else if (_szName == "FSMBalista")
		{
			return new FSMBalista;
		}
		else if (_szName == "FSMSteeringPeon")
		{
			return new FSMSteeringPeon;
		}
		else if (_szName == "FSMHQ")
		{
			return new FSMHQ;
		}
		return nullptr;
	}
};

#endif
