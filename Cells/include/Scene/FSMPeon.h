/***************************************************/
/* Nom:	FSMPeon.h
/* Description: FSMPeon
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __FSMPeon_H_
#define __FSMPeon_H_

#include "AI\StateMachine.h"
#include "FSMPeonLive.h"
#include "Scripts\CharacterController.h"

using namespace crea;

class FSMPeon : public StateMachine
{
	Entity*			m_pEntity;
	CharacterController* m_pCharacterController;

	int				m_iLife;
	FSMPeonLive*	m_pFSMPeonLive;

public:
	FSMPeon(Agent* _pAgent);
	virtual ~FSMPeon();

	inline FSMPeonLive* getFSMPeonLive() { return m_pFSMPeonLive; }

	virtual bool States(StateMachineEvent _event, Msg* _msg, int _state);

};

#endif
