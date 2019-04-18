/***************************************************/
/* Nom:	FSMHQ.h
/* Description: FSMHQ
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __FSMHQ_H_
#define __FSMHQ_H_

#include "AI\StateMachine.h"
#include "AI\Planning\Planner.h"
#include "AI\Planning\WorldState.h"

using namespace crea;

class FSMHQ : public StateMachine
{
	GameManager*	m_pGM;
	Entity*			m_pEntity;
	Entity*			m_pMiner;
	Entity*			m_pWoodCutter;
	Entity*			m_pBlackSmith;
	Entity*			m_pLogger;

	vector<goap::Action>	m_actionsPossible;
	goap::Planner			m_planner;
	goap::WorldState		m_initState;
	goap::WorldState		m_goalState;
	vector<goap::Action>	m_actionsToDo;
	
public:
	FSMHQ();
	virtual ~FSMHQ();
	
	virtual bool States(StateMachineEvent _event, Msg* _msg, int _state);

	virtual Component* clone() { return new FSMHQ(*this); }

};

#endif
