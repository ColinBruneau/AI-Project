#include "stdafx.h"

#include "Game\FSMPeon.h"
#include <string.h>


//Add new states here
enum States {
	STATE_Initialize,
	STATE_Wander
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

		OnMsg(MSG_ChangeState) //Default msg response (if not handled inside current state)

							   ///////////////////////////////////////////////////////////////
		State(STATE_Initialize)
		OnEnter

		OnMsg(MSG_Timeout)

		OnUpdate

		cout << "Peon initialize " << this->m_Owner->GetID() << endl;

		OnExit


		///////////////////////////////////////////////////////////////
		State(STATE_Wander)

		OnMsg(MSG_ChangeState)

		OnUpdate


		EndStateMachine
}