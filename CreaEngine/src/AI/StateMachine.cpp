// Portions Copyright (C) Steve Rabin, 2001
#include "stdafx.h"

#include "AI\StateMachine.h"

namespace crea
{

	StateMachine::StateMachine()
	{
		m_currentState = 0;
		m_stateChange = false;
		m_nextState = false;
		m_timeOnEnter = 0.0f;
		m_ccMessagesToAgent = 0;
		m_stack.push_back(m_currentState);
	}

	StateMachine::~StateMachine()
	{
	}

	void StateMachine::Initialize(Entity* _pOwner)
	{
		m_Owner = _pOwner;
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
		int safetyCount = 10;
		while (m_stateChange && (--safetyCount >= 0))
		{
			assert(safetyCount > 0 && "StateMachine::Process - Scenes are flip-flopping in an infinite loop.");

			m_stateChange = false;

			// Let the last state clean-up
			States(EVENT_Exit, 0, m_currentState);

			// Set the new state
			m_currentState = m_nextState;

			// Add the state to the stack
			m_stack.push_back(m_currentState);
			if (m_stack.size() > MAX_STATES_IN_STACK)
			{
				m_stack.pop_front();
			}

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

	int StateMachine::SetStateInHistory()
	{
		// Can't set previous state if only 1 state in queue
		if (m_stack.size() == 1)
			return false;

		m_stateChange = true;
		m_stack.pop_back();
		m_nextState = m_stack.back();
		return m_nextState;
	}

	void StateMachine::SendMsg(int name, objectID receiver, void* data)
	{
		g_msgmanager->sendMsg(0, name, m_Owner->GetID(), receiver, -1, data);

	}


	void StateMachine::SendDelayedMsg(float delay, int name, objectID receiver, void* data)
	{
		g_msgmanager->sendMsg(delay, name, m_Owner->GetID(), receiver, -1, data);

	}


	void StateMachine::SendDelayedMsgToMe(float delay, int name, MSG_Scope scope)
	{
		if (scope == SCOPE_TO_THIS_STATE) {
			g_msgmanager->sendMsg(delay, name, m_Owner->GetID(), m_Owner->GetID(), m_currentState);
		}
		else {
			g_msgmanager->sendMsg(delay, name, m_Owner->GetID(), m_Owner->GetID(), -1);
		}

	}

}


