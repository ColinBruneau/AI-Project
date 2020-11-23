/***************************************************/
/* Nom:	FSMPeonLive.h
/* Description: FSMPeonLive
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __FSMPeonLive_H_
#define __FSMPeonLive_H_

#include "AI\StateMachine.h"
#include "Scripts\CharacterController.h"
#include "FSMPeonGoTo.h"

using namespace crea;

//Add new states here
enum StatesFSMPeonLive {
	STATE_Init,
	STATE_Idle,
	STATE_GoTo,
	STATE_GetResource,
	STATE_DropResource,
	STATE_Hit,
	STATE_Build,
	STATE_Mine,
	STATE_Harvest,
	STATE_Kill
};

class FSMPeonLive : public StateMachine
{
	GameManager*	m_pGM;
	Entity*			m_pEntity;
	CharacterController* m_pCharacterController;
	SpriteRenderer* m_pSpriteRenderer;
	Agent*			m_pAgent;

	FSMPeonGoTo*	m_pFSMPeonGoTo;

	Entity*			m_pMine;
	Entity*			m_pHQ;
	Entity*			m_pTarget;
	Vector2f		m_vTarget;
	Entity*			m_pTree;
	Entity*			m_pMiner;
	Entity*			m_pWoodCutter;
	Entity*			m_pBlackSmith;
	Entity*			m_pLogger;

	EnumAnimCondition m_condition;

	bt::BehaviorTree m_bt;

	short			m_iToolPV;

public:
	FSMPeonLive();
	virtual ~FSMPeonLive();

	void setEntity(Entity* _p) { m_pEntity = _p; }
	void setCharacterController(CharacterController* _p) { m_pCharacterController = _p; }
	inline FSMPeonGoTo* getFSMPeonGoTo() { return m_pFSMPeonGoTo; }

	virtual bool States(StateMachineEvent _event, Msg* _msg, int _state);

	virtual Component* clone() { return new FSMPeonLive(*this); }
};

#endif
