#include "stdafx.h"

#include "Scene\FSMPeon.h"
#include "Scene\Messages.h"
#include <string.h>


//Add new states here
enum States {
	STATE_Spawn,
	STATE_Live,
	STATE_Die
};

FSMPeon::FSMPeon(Agent* _pAgent) : StateMachine(_pAgent)
{
	// Get Entity
	m_pEntity = _pAgent->getEntity();
	// Get CharacterController
	m_pCharacterController = m_pEntity->getComponent<CharacterController>();
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

		OnOtherMsg()
			m_pFSMPeonLive->States(_event, _msg, _state); // CB: propagate msg

		///////////////////////////////////////////////////////////////
		State(STATE_Spawn)
		OnEnter
			m_iLife = 100;

		OnUpdate
			SetState(STATE_Live);

		OnExit

		///////////////////////////////////////////////////////////////
		State(STATE_Live)
		OnEnter
			m_pFSMPeonLive = new FSMPeonLive(this->m_Owner);
			m_pFSMPeonLive->Initialize();

		OnUpdate
			m_pFSMPeonLive->Update();
			if (m_iLife <= 0)
			{
				SetState(STATE_Die);
			}

		OnExit
			delete m_pFSMPeonLive;
			m_pFSMPeonLive = nullptr;


		///////////////////////////////////////////////////////////////
		State(STATE_Die)
		OnEnter

		OnUpdate
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Die);

			OnExit

	EndStateMachine
}
