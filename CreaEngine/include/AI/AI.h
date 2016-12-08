/***************************************************/
/* Nom:	AI.h
/* Description: AI
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __AI_H_
#define __AI_H_

#include "Core\singleton.h"

namespace crea
{

	#define g_time TimeManager::getSingleton()
	#define g_agentmanager AgentManager::getSingleton()
	#define g_msgmanager MsgManager::getSingleton()
	#define g_debuglog DebugLog::getSingleton()

	#define INVALID_OBJECT_ID 0
	typedef unsigned int objectID;

}

#include "StateMachine.h"
#include "AgentManager.h"
#include "Agent.h"
#include "MsgManager.h"
#include "Msg.h"

#endif