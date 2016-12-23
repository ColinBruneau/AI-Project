#include "stdafx.h"

#include "Game\FSMPeonLive.h"
#include "Game\Messages.h"
#include <string.h>


//Add new states here
enum States {
	STATE_Idle,
	STATE_GoTo,
	STATE_GetResource,
	STATE_DropResource,
	STATE_Hit
};

FSMPeonLive::FSMPeonLive(Agent* _pAgent) : StateMachine(_pAgent)
{
	// Get Entity
	m_pEntity = _pAgent->getEntity();
	// Get CharacterController
	m_pCharacterController = m_pEntity->getComponent<CharacterController>();
	// Get HQ
	m_pHQ = m_pGM->getEntity("QG");
	// Get mine
	m_pMine = m_pGM->getEntity("Mine");

}

FSMPeonLive::~FSMPeonLive()
{

}

bool FSMPeonLive::States(StateMachineEvent _event, Msg* _msg, int _state)
{
	BeginStateMachine

		OnMsg(MSG_Hit)
			SetState(STATE_Hit);
		OnMsg(MSG_HitStop)
			SetStateInHistory();

 	    ///////////////////////////////////////////////////////////////
		State(STATE_Idle)
		OnEnter
			SendDelayedMsgToMe(0.5f, MSG_Hit);
 
		OnUpdate
			if (m_pMine)
			{
				m_pTarget = m_pMine;
				m_vTarget = m_pTarget->getPosition() + Vector2f(20.f, 80.f);
				m_pCharacterController->setCondition(kACond_Default);
				SetState(STATE_GoTo);
			}

		OnExit


		///////////////////////////////////////////////////////////////
		State(STATE_GoTo)
		OnEnter
			m_pFSMPeonGoTo = new FSMPeonGoTo(this->m_Owner, m_vTarget);
			m_pFSMPeonGoTo->Initialize();

		OnUpdate
			m_pFSMPeonGoTo->Update();
			if (m_pFSMPeonGoTo->GetState() == FSMPeonGoTo::STATE_CompletedPath)
			{
				if (m_pTarget == m_pMine)
					SetState(STATE_GetResource);
				else
					SetState(STATE_DropResource);
			}

		OnExit
			delete m_pFSMPeonGoTo;

			///////////////////////////////////////////////////////////////
		State(STATE_GetResource)
		OnEnter
			m_pTarget = m_pHQ;
			m_vTarget = m_pTarget->getPosition() + Vector2f(80.f, 100.f);
			m_pCharacterController->setCondition(kACond_Gold);

		OnUpdate
			SetState(STATE_GoTo);

		OnExit
			
		///////////////////////////////////////////////////////////////
		State(STATE_DropResource)
		OnEnter

		OnUpdate
			SetState(STATE_Idle);

		OnExit

			///////////////////////////////////////////////////////////////
		State(STATE_Hit)
		OnEnter
			// CB: a hit is a temporary death...
			SendDelayedMsgToMe(0.5f, MSG_HitStop);

		OnUpdate
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Die);

		OnExit
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Default);

	EndStateMachine
}