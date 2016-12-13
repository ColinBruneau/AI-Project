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
	Entity*			m_pEntity;
	CharacterController* m_pCharacterController;
	
	Entity*			m_pMine;
	Entity*			m_pHQ;
	Entity*			m_pTarget;
	Vector2f		m_vTarget;

	bool GoTo(Vector2f& _vTargetPosition);

public:
	FSMPeon(Agent* _pAgent);
	virtual ~FSMPeon();

	void setEntity(Entity* _p) { m_pEntity = _p; }
	void setCharacterController(CharacterController* _p) { m_pCharacterController = _p; }

	virtual bool States(StateMachineEvent _event, Msg* _msg, int _state);

};

#endif
