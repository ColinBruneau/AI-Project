#include "stdafx.h"

#include "Scripts\FSMPeon.h"
#include "Scripts\Messages.h"
#include <string.h>


//Add new states here
enum States {
	STATE_Spawn,
	STATE_Live,
	STATE_Die,
};

FSMPeon::FSMPeon()
{

}

FSMPeon::~FSMPeon()
{

}

bool FSMPeon::States(StateMachineEvent _event, Msg* _msg, int _state)
{
	BeginStateMachine

		OnMsg(MSG_Reset)
			SetState(STATE_Spawn);
	
		OnMsg(MSG_Die)
			SetState(STATE_Die);		
		
		OnMsg(MSG_Hit)
			m_iLife -= 1;
			m_pAgent->setHealth(m_iLife);
			if (m_iLife <= 0)
			{
				SetState(STATE_Die);
			}
			if (m_pFSMPeonLive)
			{
				m_pFSMPeonLive->States(_event, _msg, _state); // CB: propagate msg to sub-state
			}

		OnMsg(MSG_Boost)
			m_pAgent->setDexterity(m_pAgent->getDexterity()+1);

		///////////////////////////////////////////////////////////////
		State(STATE_Spawn)
		OnEnter
			// Get Entity
			m_pEntity = getEntity();
			// Get CharacterController
			m_pCharacterController = m_pEntity->getComponent<CharacterController>();
			// Get Agent
			m_pAgent = m_pEntity->getComponent<Agent>();

			m_iLife = m_pAgent->getHealth();

		OnUpdate
			SetState(STATE_Live);

		///////////////////////////////////////////////////////////////
		State(STATE_Live)
		OnEnter
			m_pFSMPeonLive = new FSMPeonLive();
			m_pEntity->addComponent(m_pFSMPeonLive);
			m_pFSMPeonLive->Initialize(m_pEntity);

		OnUpdate
			//m_pFSMPeonLive->Update(); // CBruneau: not necessary as it was added as a component
			if (m_iLife <= 0)
			{
				SetState(STATE_Die);
			}

			OnExit
			m_pEntity->removeComponent(m_pFSMPeonLive);
			delete m_pFSMPeonLive;
			m_pFSMPeonLive = nullptr;
			
		///////////////////////////////////////////////////////////////
		State(STATE_Die)
		OnEnter
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Die);

EndStateMachine
}