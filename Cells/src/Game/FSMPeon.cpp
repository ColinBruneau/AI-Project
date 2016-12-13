#include "stdafx.h"

#include "Game\FSMPeon.h"
#include <string.h>


//Add new states here
enum States {
	STATE_Idle,
	STATE_GoTo,
	STATE_GetResource,
	STATE_DropResource
};

FSMPeon::FSMPeon(Agent* _pAgent) : StateMachine(_pAgent)
{

}

FSMPeon::~FSMPeon()
{

}

bool FSMPeon::States(StateMachineEvent _event, Msg* _msg, int _state)
{
	BeginStateMachine

 	    ///////////////////////////////////////////////////////////////
		State(STATE_Idle)
		OnEnter
			cout << "Peon Idle " << this->m_Owner->GetID() << endl;
			m_pMine = nullptr;
 
		OnUpdate
			// Get mine
			m_pMine = m_pGM->getEntity("Mine");
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
			cout << "Peon GoTo " << this->m_Owner->GetID() << endl;

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
			cout << "Peon GetResource " << this->m_Owner->GetID() << endl;
			// Get HQ
			m_pHQ = m_pGM->getEntity("QG");
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
			cout << "Peon DropResource " << this->m_Owner->GetID() << endl;


		OnUpdate
			SetState(STATE_Idle);

		OnExit

	EndStateMachine
}

bool FSMPeon::GoTo(Vector2f& _vTargetPosition)
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

	vVelocity.normalize();
	m_pCharacterController->move(vVelocity * (float)TimeManager::getSingleton()->getFrameTime().asSeconds());

	return bArrived;
}