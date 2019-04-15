/***************************************************/
/* Nom:	Actions.h
/* Description: Actions
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Actions_H_
#define __Actions_H_

#include "AI\BehaviorTree\Behavior.h"

using namespace crea;
using namespace bt;

class ActionSeekTo : public bt::Behavior
{
	Steering* m_pSteering;
	Seek* m_pSeek;
	float m_fArrivedDistance;
	Vector2f m_vOffset;

public:
	ActionSeekTo(Seek* _pSeek, float _fArrivedDistance, Vector2f _vOffset = Vector2f(0.f, 0.f))
		: m_fArrivedDistance(_fArrivedDistance), m_vOffset(_vOffset)
	{
		m_pSeek = _pSeek;
		m_pSteering = m_pSeek->getEntity()->getComponent<Steering>();
	}

	virtual ~ActionSeekTo()
	{
	}

	virtual void onInitialize()
	{
		if (m_pSteering)
		{
			m_pSteering->addBehavior(m_pSeek, 1.0f);
		}
	}

	virtual void onTerminate(Status s)
	{
		if (m_pSteering)
		{
			m_pSteering->removeBehavior(m_pSeek);
		}
	}

	virtual Status update()
	{
		if (!m_pSteering)
		{
			return BH_FAILURE;
		}

		Vector2f targetOffset = m_pSeek->getTarget()->getPosition() + m_vOffset - m_pSeek->getEntity()->getPosition();
		double distance = targetOffset.length();

		if (distance < m_fArrivedDistance)
		{
			return BH_SUCCESS;
		}
		else
		{
			return BH_RUNNING;
		}
	}

	virtual Behavior* clone()
	{
		return new ActionSeekTo(*this);
	}
};

class ActionFleeUntil : public bt::Behavior
{
	Steering* m_pSteering;
	Flee* m_pFlee;
	float m_fDistanceToFlee;

public:
	ActionFleeUntil(Flee* _pFlee, float _fDistanceToFlee)
		: m_fDistanceToFlee(_fDistanceToFlee)
	{
		m_pFlee = _pFlee;
		m_pSteering = m_pFlee->getEntity()->getComponent<Steering>();
	}

	virtual ~ActionFleeUntil()
	{
	}

	virtual void onInitialize()
	{
		if (m_pSteering)
		{
			m_pSteering->addBehavior(m_pFlee, 1.0f);
		}
	}

	virtual void onTerminate(Status s)
	{
		if (m_pSteering)
		{
			m_pSteering->removeBehavior(m_pFlee);
		}
	}

	virtual Status update()
	{
		if (!m_pSteering)
		{
			return BH_FAILURE;
		}

		Vector2f targetOffset = m_pFlee->getTarget()->getPosition() - m_pFlee->getEntity()->getPosition();
		double distance = targetOffset.length();

		if (distance > m_fDistanceToFlee)
		{
			return BH_SUCCESS;
		}
		else
		{
			return BH_RUNNING;
		}
	}

	virtual Behavior* clone()
	{
		return new ActionFleeUntil(*this);
	}
};

class ActionWander : public bt::Behavior
{
	Steering* m_pSteering;
	Wander* m_pWander;

public:
	ActionWander(Wander* _pWander)
	{
		m_pWander = _pWander;
		m_pSteering = m_pWander->getEntity()->getComponent<Steering>();
	}

	virtual ~ActionWander()
	{
	}

	virtual void onInitialize()
	{
		if (m_pSteering)
		{
			m_pSteering->addBehavior(m_pWander, 1.0f);
		}
	}

	virtual void onTerminate(Status s)
	{
		if (m_pSteering)
		{
			m_pSteering->removeBehavior(m_pWander);
		}
	}

	virtual Status update()
	{
		if (!m_pSteering)
		{
			return BH_FAILURE;
		}

		return BH_RUNNING;
	}

	virtual Behavior* clone()
	{
		return new ActionWander(*this);
	}
};

class DecoratorIsCloseToTarget : public Decorator
{
	Entity* m_pEntity;
	Entity* m_pTarget;
	float m_fDistance;

public:
	DecoratorIsCloseToTarget(Entity* _pEntity, Entity* _pTarget, float _fDistance)
	{
		m_pEntity = _pEntity;
		m_pTarget = _pTarget;
		m_fDistance = _fDistance;
	}

	virtual ~DecoratorIsCloseToTarget()
	{
	}

	virtual void onInitialize()
	{
	}

	virtual void onTerminate(Status s)
	{
		m_pChild->onTerminate(s);
	}

	virtual Status update()
	{
		Vector2f targetOffset = m_pEntity->getPosition() - m_pTarget->getPosition();
		double distance = targetOffset.length();

		if (distance < m_fDistance)
		{
			Status s = m_pChild->tick();
			return s;
		}
		else
		{
			abort();
			return BH_FAILURE;
		}
	}

	virtual Behavior* clone()
	{
		return new DecoratorIsCloseToTarget(*this);
	}
};

class DecoratorRepeat : public Decorator
{
public:
	DecoratorRepeat(Behavior* child, int count)
		: Decorator(child), m_iLimit(count)
	{
	}

	void setCount(int count)
	{
		m_iLimit = count;
	}

	void onInitialize()
	{
		m_iCounter = 0;
	}

	Status update()
	{
		for (;;)
		{
			m_pChild->tick();
			if (m_pChild->getStatus() == BH_RUNNING) return BH_RUNNING;
			if (m_pChild->getStatus() == BH_FAILURE) return BH_FAILURE;
			if (++m_iCounter == m_iLimit)
				return BH_SUCCESS;
			m_pChild->reset();
		}
		return BH_INVALID;
	}

	virtual Behavior* clone()
	{
		return new DecoratorRepeat(*this);
	}

protected:
	int m_iLimit;
	int m_iCounter;
};

class DecoratorTimer : public Decorator
{
public:
	DecoratorTimer(float _fTime)
		: m_fTimeLimit(_fTime)
	{
	}

	void setTimeLimit(float _fTime)
	{
		m_fTimeLimit = _fTime;
	}

	void onInitialize()
	{
		m_fTime = 0.f;
	}

	virtual void onTerminate(Status s)
	{
		m_pChild->abort();
		m_pChild->reset();
	}

	Status update()
	{
		Time frameTime = TimeManager::getSingleton()->getFrameTime();
		m_fTime += (float)frameTime.asSeconds();
		if (m_fTime >= m_fTimeLimit)
			return BH_SUCCESS;

		return m_pChild->tick();
	}

	virtual Behavior* clone()
	{
		return new DecoratorTimer(*this);
	}

protected:
	float m_fTimeLimit;
	float m_fTime;
};

class DecoratorEntityNameIs : public Decorator
{
public:
	DecoratorEntityNameIs(Entity* _pEntity, string _szName)
	{
		m_pEntity = _pEntity;
		m_szName = _szName;
	}

	void setName(string _szName)
	{
		m_szName = _szName;
	}

	void onInitialize()
	{

	}

	virtual void onTerminate(Status s)
	{
	}

	Status update()
	{
		if (m_szName != m_pEntity->getName())
		{
			return BH_FAILURE;
		}

		return m_pChild->tick();
	}

	virtual Behavior* clone()
	{
		return new DecoratorEntityNameIs(*this);
	}

protected:
	string m_szName;
	Entity* m_pEntity;

};

class ActionAnimation : public bt::Behavior
{
	CharacterController* m_pCharacterController;
	EnumAction m_action;
	EnumAnimCondition m_condition;

public:
	ActionAnimation(Entity* _pEntity, EnumAction _action, EnumAnimCondition _condition)
		: m_action(_action), m_condition(_condition)
	{
		m_pCharacterController = _pEntity->getComponent<CharacterController>();
	}

	virtual ~ActionAnimation()
	{
	}

	virtual void onInitialize()
	{
	}

	virtual void onTerminate(Status s)
	{
	}

	virtual Status update()
	{
		if (!m_pCharacterController)
		{
			return BH_FAILURE;
		}

		m_pCharacterController->setCondition(m_condition);
		m_pCharacterController->setAction(m_action);

		return BH_RUNNING;
	}

	virtual Behavior* clone()
	{
		return new ActionAnimation(*this);
	}
};

class ActionSteer : public bt::Behavior
{
	Steering* m_pSteering;
	Steering* m_pSteeringForBehaviors;

public:
	ActionSteer(Entity* _pEntity, Steering* _pSteeringForBehaviors)
		: m_pSteeringForBehaviors(_pSteeringForBehaviors)
	{
		m_pSteering = _pEntity->getComponent<Steering>();
	}

	virtual ~ActionSteer()
	{
	}

	virtual void onInitialize()
	{
		if (m_pSteering)
		{
			vector<PairFloatBehavior*>* behaviors = m_pSteeringForBehaviors->getBehaviors();
			for (unsigned int i = 0; i < behaviors->size(); i++)
			{
				PairFloatBehavior* pFloatBehavior = (*behaviors)[i];
				m_pSteering->addBehavior(pFloatBehavior->second, pFloatBehavior->first);
			}
		}
	}

	virtual void onTerminate(Status s)
	{
		if (m_pSteering)
		{
			vector<PairFloatBehavior*>* behaviors = m_pSteeringForBehaviors->getBehaviors();
			for (unsigned int i = 0; i < behaviors->size(); i++)
			{
				PairFloatBehavior* pFloatBehavior = (*behaviors)[i];
				m_pSteering->removeBehavior(pFloatBehavior->second);
			}
		}
	}

	virtual Status update()
	{
		if (!m_pSteering)
		{
			return BH_FAILURE;
		}
		
		return BH_RUNNING;
	}

	virtual Behavior* clone()
	{
		return new ActionSteer(*this);
	}
};

#endif
