// Portions Copyright (C) Steve Rabin, 2001
#ifndef __AgentManager_H__
#define __AgentManager_H__

#include "AI.h"

namespace crea
{

	class Agent;
	class CREAENGINE_API MapobjectIDAgent : public map<objectID, Agent*> {};

	class CREAENGINE_API AgentManager : public Singleton <AgentManager>
	{
	public:

		AgentManager();
		~AgentManager();

		void store(Agent& _agent);
		void remove(objectID _id);
		Agent* find(objectID _id);

		objectID getNewObjectID();

	private:

		objectID nextFreeID;

		MapobjectIDAgent m_Agents;
	};

}
#endif	// __AgentManager_H__