// Portions Copyright (C) Steve Rabin, 2001
#include "stdafx.h"

#include "AI\AgentManager.h"
#include "AI\AI.h"
#include "AI\Agent.h"

namespace crea
{

	AgentManager::AgentManager()
	{
		nextFreeID = 1;
	}


	AgentManager::~AgentManager()
	{

	}


	void AgentManager::store(Agent & _agent)
	{
		if (find(_agent.GetID()) == 0) {
			m_Agents[_agent.GetID()] = &_agent;
		}
		else {
			assert(!"AgentManager::Store - Object ID already represented in database.");
		}
	}


	void AgentManager::remove(objectID _id)
	{
		MapobjectIDAgent::iterator it = m_Agents.find(_id);
		if (it != m_Agents.end())
		{
			m_Agents.erase(it);
		}

		return;
	}


	Agent* AgentManager::find(objectID _id)
	{
		MapobjectIDAgent::iterator it = m_Agents.find(_id);
		if (it != m_Agents.end())
		{
			return it->second;
		}

		return(0);

	}


	objectID AgentManager::getNewObjectID()
	{
		return(nextFreeID++);

	}

}