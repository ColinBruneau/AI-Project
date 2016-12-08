// Portions Copyright (C) Steve Rabin, 2001
#include "stdafx.h"

#include "AI\StateMachine.h"

namespace crea
{

	StateMachine::StateMachine(Agent * object)
	{
		m_Owner = object;
		m_currentState = 0;
		m_stateChange = false;
		m_nextState = false;
		m_timeOnEnter = 0.0f;
		m_ccMessagesToAgent = 0;
	}


	void StateMachine::Initialize(void)
	{
		Process(EVENT_Enter, 0);
	}


	void StateMachine::Update(void)
	{
		Process(EVENT_Update, 0);
	}


	void StateMachine::Process(StateMachineEvent event, Msg * msg)
	{

		if (event == EVENT_Message && msg && GetCCReceiver() > 0)
		{	// CC this message
			SendMsg(msg->GetMsgName(), GetCCReceiver());
		}

		if (States(event, msg, m_currentState) == false)
		{	// Current state didn't handle msg, try Global state (-1)
			States(event, msg, -1);
		}

		// Check for a state change
		int safetyCount = 50;
		while (m_stateChange && (--safetyCount >= 0))
		{
			assert(safetyCount > 0 && "StateMachine::Process - GameStates are flip-flopping in an infinite loop.");

			m_stateChange = false;

			// Let the last state clean-up
			States(EVENT_Exit, 0, m_currentState);

			// Set the new state
			m_currentState = m_nextState;

			// Remember the time we entered this state
			m_timeOnEnter = g_time->getGameTime().asSeconds();

			// Let the new state initialize
			States(EVENT_Enter, 0, m_currentState);
		}

	}


	void StateMachine::SetState(unsigned int newState)
	{
		m_stateChange = true;
		m_nextState = newState;

	}


	void StateMachine::SendMsg(MSG_Name name, objectID receiver, void* data)
	{
		g_msgmanager->sendMsg(0, name, m_Owner->GetID(), receiver, -1, data);

	}


	void StateMachine::SendDelayedMsg(float delay, MSG_Name name, objectID receiver, void* data)
	{
		g_msgmanager->sendMsg(delay, name, m_Owner->GetID(), receiver, -1, data);

	}


	void StateMachine::SendDelayedMsgToMe(float delay, MSG_Name name, MSG_Scope scope)
	{
		if (scope == SCOPE_TO_THIS_STATE) {
			g_msgmanager->sendMsg(delay, name, m_Owner->GetID(), m_Owner->GetID(), m_currentState);
		}
		else {
			g_msgmanager->sendMsg(delay, name, m_Owner->GetID(), m_Owner->GetID(), -1);
		}

	}

}


