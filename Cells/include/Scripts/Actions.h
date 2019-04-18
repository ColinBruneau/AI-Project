/***************************************************/
/* Nom:	Actions.h
/* Description: Actions
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Actions_H_
#define __Actions_H_

#include "AI\BehaviorTree\Behavior.h"
#include "Scene\ScenePlanning.h"

class ActionSendMsg : public bt::Behavior
{
protected:
	FSMPeonLive * m_pFSM;
	int m_MSG_type;

public:

	ActionSendMsg(FSMPeonLive* _pFSM, int _MSG_type)
		: m_pFSM(_pFSM), m_MSG_type(_MSG_type)
	{
	}

	virtual void onInitialize()
	{
		m_pFSM->SendDelayedMsgToMe(0.0f, m_MSG_type);
	}

	virtual bt::Status update()
	{
		return bt::BH_SUCCESS;
	}

	virtual Behavior* clone()
	{
		return new ActionSendMsg(*this);
	}
};

class ActionGoTo : public bt::Behavior
{
protected:
	FSMPeonLive* m_pFSM;
	int m_MSG_Goto_type;

public:

	ActionGoTo(FSMPeonLive* _pFSM, int _MSG_Goto_type)  
		: m_pFSM(_pFSM), m_MSG_Goto_type(_MSG_Goto_type)
	{
	}

	virtual void onInitialize()
	{
		m_pFSM->SendDelayedMsgToMe(0.0f, m_MSG_Goto_type);
	}

	virtual bt::Status update()
	{
		if (m_pFSM->GetState() == STATE_GoTo)
		{
			// tester arrivée
			if (m_pFSM->getFSMPeonGoTo()->GetState() == FSMPeonGoTo::STATE_CompletedPath)
			{
				return bt::BH_SUCCESS;
			}
			else if(m_pFSM->getFSMPeonGoTo()->GetState() == FSMPeonGoTo::STATE_SearchFailed)
			{
				return bt::BH_FAILURE;
			}
			return bt::BH_RUNNING;
		}

		return bt::BH_FAILURE;
	}

	virtual Behavior* clone()
	{
		return new ActionGoTo(*this);
	}
};

class ActionSetCondition : public bt::Behavior
{
protected:
	CharacterController* m_pCC;
	EnumAnimCondition m_eCondition;

public:

	ActionSetCondition(CharacterController* _pCC, EnumAnimCondition _eCondition)
		: m_pCC(_pCC), m_eCondition(_eCondition)
	{ }

	virtual void onInitialize()
	{
		m_pCC->setCondition(m_eCondition);
	}

	virtual bt::Status update()
	{
		return bt::BH_SUCCESS;
	}

	virtual Behavior* clone()
	{
		return new ActionSetCondition(*this);
	}
};

class ActionSetAction : public bt::Behavior
{
protected:
	CharacterController * m_pCC;
	EnumAction m_eAction;

public:

	ActionSetAction(CharacterController* _pCC, EnumAction _eAction)
		: m_pCC(_pCC), m_eAction(_eAction)
	{ }

	virtual void onInitialize()
	{
		m_pCC->setAction(m_eAction);
	}

	virtual bt::Status update()
	{
		return bt::BH_RUNNING;
	}

	virtual Behavior* clone()
	{
		return new ActionSetAction(*this);
	}
};

class PreCondition : public bt::Behavior
{
protected:
	Blackboard * m_pBB;
	string m_variable;
	string m_value;

public:

	PreCondition(Blackboard* _pBB, const string& _variable, const string& _value)
		: m_pBB(_pBB), m_variable(_variable), m_value(_value)
	{ }

	virtual bt::Status update()
	{
		/*
		if (m_variable == "HqHaveLogs")
		{
			cout << "Precond: " << m_variable << " " << m_value << endl;
		}*/
		if (m_pBB->getVariable(m_variable) == m_value)
		{
			return bt::BH_SUCCESS;
		}
		else
		{
			return bt::BH_FAILURE;
		}
	}

	virtual Behavior* clone()
	{
		return new PreCondition(*this);
	}
};

class Effect : public bt::Behavior
{
protected:
	Blackboard * m_pBB;
	string m_variable;
	string m_value;

public:

	Effect(Blackboard* _pBB, const string& _variable, const string& _value)
		: m_pBB(_pBB), m_variable(_variable), m_value(_value)
	{ }

	virtual bt::Status update()
	{
		cout << "Effect: " << m_variable << " " << m_value << endl;
		m_pBB->setVariable(m_variable, m_value);
		return bt::BH_SUCCESS;
	}

	virtual Behavior* clone()
	{
		return new Effect(*this);
	}
};

class FilterIsEntity : public bt::Decorator
{
	FSMPeonLive * m_pFSM;
	Entity* m_pEntity;

public:
	FilterIsEntity(FSMPeonLive* _pFSM, Entity* _pEntity)
		: m_pFSM(_pFSM), m_pEntity(_pEntity)
	{}

	virtual bt::Status update()
	{
		if (m_pFSM->getEntity() == m_pEntity)
		{
			return m_pChild->tick();
		}
		else
		{
			return bt::BH_FAILURE;
		}
	}

	virtual Behavior* clone()
	{
		return new FilterIsEntity(*this);
	}
};

class FilterTimer : public bt::Decorator
{
	Time m_timeMax;
	Clock m_timer;

public:
	FilterTimer(Time _timeMax)
		: m_timeMax(_timeMax)
	{}

	virtual void onInitialize()
	{
		m_timer.restart();
	}

	virtual bt::Status update()
	{
		if (m_timer.getElapsedTime().asSeconds() > m_timeMax.asSeconds())
		{
			m_pChild->abort();
			return bt::BH_SUCCESS;
		}
		else
		{
			return  m_pChild->tick();
		}
	}

	virtual Behavior* clone()
	{
		return new FilterTimer(*this);
	}
};

class ActionWait : public bt::Behavior
{
protected:

public:

	ActionWait()
	{ }

	virtual bt::Status update()
	{
		return bt::BH_RUNNING;
	}

	virtual Behavior* clone()
	{
		return new ActionWait(*this);
	}
};

class ActionActivateSpriteRenderer : public bt::Behavior
{
protected:
	SpriteRenderer* m_pSpriteRenderer;
	bool m_bActive;

public:

	ActionActivateSpriteRenderer(SpriteRenderer* _pSpriteRenderer, bool _bActive)
		: m_pSpriteRenderer(_pSpriteRenderer), m_bActive(_bActive)
	{ }

	virtual void onInitialize()
	{
		m_pSpriteRenderer->setActive(m_bActive);
	}

	virtual bt::Status update()
	{
		return bt::BH_SUCCESS;
	}

	virtual Behavior* clone()
	{
		return new ActionActivateSpriteRenderer(*this);
	}
};

#endif
