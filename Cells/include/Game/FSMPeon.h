/***************************************************/
/* Nom:	Peon.h
/* Description: Peon
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Peon_H_
#define __Peon_H_

#include "AI\StateMachine.h"

using namespace crea;

class FSMPeon : public StateMachine
{
	GameManager*	m_pGM;

public:
	FSMPeon(Agent* _pAgent);
	virtual ~FSMPeon();

	virtual bool States(StateMachineEvent _event, Msg* _msg, int _state);

};

#endif
