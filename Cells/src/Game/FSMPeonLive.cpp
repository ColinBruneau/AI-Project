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

		OnUpdate
			if (GoTo(m_vTarget))
			{
				if (m_pTarget == m_pMine)
					SetState(STATE_GetResource);
				else
					SetState(STATE_DropResource);
			}

		OnExit

			///////////////////////////////////////////////////////////////
		State(STATE_GetResource)
		OnEnter
			m_pTarget = m_pHQ;
			m_vTarget = m_pTarget->getPosition() + Vector2f(80.f, 100.f);
			m_pCharacterController->setCondition(kACond_Gold);

		OnUpdate
			if (GoTo(m_vTarget))
			{
				SetState(STATE_GoTo);
			}

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

bool FSMPeonLive::GoTo(Vector2f& _vTargetPosition)
{
	bool bArrived = false;
	Vector2f vEntityPosition = m_pEntity->getPosition();
	Vector2f vVelocity = _vTargetPosition - vEntityPosition;
	if (vVelocity.length() > 10)
	{
		int iDirection = 0;
		Vector2f vRight(0.0f, -1.f);
		float fAngle = vRight.angle(vVelocity);
		if (vVelocity.getX() > 0)
		{
			iDirection = (int)(0.5f + fAngle * 4 / 3.14f);
			m_pCharacterController->setDirection((EnumCharacterDirection)iDirection);
		}
		else
		{
			iDirection = 8 - (int)(0.5f + fAngle * 4 / 3.14f);
			iDirection = (iDirection == 8) ? 0 : iDirection;
			m_pCharacterController->setDirection((EnumCharacterDirection)iDirection);
		}
		m_pCharacterController->setAction(kAct_Walk);
	}
	else
	{
		bArrived = true;
		vVelocity = Vector2f(0.f, 0.0f);
	}

	// CB: adjust velocity with dexterity
	int iDexterity = m_Owner->getDexterity() * 20; // cb: 200 pixels/second when dexterity at 10 

	vVelocity.normalize();
	m_pCharacterController->move(vVelocity * (float)iDexterity * (float)TimeManager::getSingleton()->getFrameTime().asSeconds());

	return bArrived;
}