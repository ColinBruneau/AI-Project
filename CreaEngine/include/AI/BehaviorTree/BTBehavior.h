/***************************************************/
/* Nom:	BTBehavior.h
/* Description: BTBehavior
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __BTBEHAVIOR_H_
#define __BTBEHAVIOR_H_

#include "AI\Steering\Behavior.h"
#include "AI\Steering\Steering.h"
#include <vector>

namespace crea
{
	// ============================================================================

	enum Status
		/**
		* Return values of and valid states for BTBehaviors.
		*/
	{
		BH_INVALID,
		BH_SUCCESS,
		BH_FAILURE,
		BH_RUNNING,
		BH_ABORTED,
	};

	class CREAENGINE_API BTBehavior
		/**
		* Base class for actions, conditions and composites.
		*/
	{
	public:
		virtual Status update() = 0;

		virtual void onInitialize() {}
		virtual void onTerminate(Status) {}

		BTBehavior()
			: m_eStatus(BH_INVALID)
		{
		}

		virtual ~BTBehavior()
		{
		}

		Status tick()
		{
			if (m_eStatus != BH_RUNNING)
			{
				onInitialize();
			}

			m_eStatus = update();

			if (m_eStatus != BH_RUNNING)
			{
				onTerminate(m_eStatus);
			}
			return m_eStatus;
		}

		void reset()
		{
			m_eStatus = BH_INVALID;
		}

		void abort()
		{
			onTerminate(BH_ABORTED);
			m_eStatus = BH_ABORTED;
		}

		bool isTerminated() const
		{
			return m_eStatus == BH_SUCCESS || m_eStatus == BH_FAILURE;
		}

		bool isRunning() const
		{
			return m_eStatus == BH_RUNNING;
		}

		Status getStatus() const
		{
			return m_eStatus;
		}

	private:
		Status m_eStatus;
	};

// ============================================================================

class CREAENGINE_API Decorator : public BTBehavior
{
protected:
	BTBehavior* m_pChild;

public:
	Decorator() {}
	Decorator(BTBehavior* child) : m_pChild(child) {}

	void addChild(BTBehavior* _pChild) { m_pChild = _pChild; }
};

class CREAENGINE_API Repeat : public Decorator
{
public:
	Repeat(BTBehavior* child)
		: Decorator(child)
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

protected:
	int m_iLimit;
	int m_iCounter;
};

// ============================================================================

class CREAENGINE_API Composite : public BTBehavior
{
public:
	void addChild(BTBehavior* child) { m_Children.push_back(child); }
	void removeChild(BTBehavior*);
	void clearChildren();
protected:
	typedef std::vector<BTBehavior*> BTBehaviors;
	BTBehaviors m_Children;
};

class CREAENGINE_API Sequence : public Composite
{
protected:
	virtual ~Sequence()
	{
	}

	virtual void onInitialize()
	{
		m_CurrentChild = m_Children.begin();
	}

	virtual Status update()
	{
		// Keep going until a child BTBehavior says it's running.
		for (;;)
		{
			Status s = (*m_CurrentChild)->tick();

			// If the child fails, or keeps running, do the same.
			if (s != BH_SUCCESS)
			{
				return s;
			}

			// Hit the end of the array, job done!
			if (++m_CurrentChild == m_Children.end())
			{
				return BH_SUCCESS;
			}
		}
	}

	virtual void onTerminate(Status s)
	{
		if (m_CurrentChild != m_Children.end())
		{
			(*m_CurrentChild)->onTerminate(s);
		}			
	}

		BTBehaviors::iterator m_CurrentChild;
	};

	// ============================================================================

	class CREAENGINE_API Selector : public Composite
	{
	protected:
		virtual ~Selector()
		{
		}

		virtual void onInitialize()
		{
			m_Current = m_Children.begin();
		}

		virtual Status update()
		{
			// Keep going until a child BTBehavior says its running.
			for (;;)
			{
				Status s = (*m_Current)->tick();

				// If the child succeeds, or keeps running, do the same.
				if (s != BH_FAILURE)
				{
					return s;
				}

				// Hit the end of the array, it didn't end well...
				if (++m_Current == m_Children.end())
				{
					return BH_FAILURE;
				}
			}
		}

		BTBehaviors::iterator m_Current;
	};

	// ----------------------------------------------------------------------------

	class CREAENGINE_API Parallel : public Composite
	{
	public:
		enum Policy
		{
			RequireOne,
			RequireAll,
		};

		Parallel(Policy forSuccess, Policy forFailure)
			: m_eSuccessPolicy(forSuccess)
			, m_eFailurePolicy(forFailure)
		{
		}

		virtual ~Parallel() {}

	protected:
		Policy m_eSuccessPolicy;
		Policy m_eFailurePolicy;

		virtual Status update()
		{
			size_t iSuccessCount = 0, iFailureCount = 0;

			for (BTBehaviors::iterator it = m_Children.begin(); it != m_Children.end(); ++it)
			{
				BTBehavior& b = **it;
				if (!b.isTerminated())
				{
					b.tick();
				}

				if (b.getStatus() == BH_SUCCESS)
				{
					++iSuccessCount;
					if (m_eSuccessPolicy == RequireOne)
					{
						return BH_SUCCESS;
					}
				}

				if (b.getStatus() == BH_FAILURE)
				{
					++iFailureCount;
					if (m_eFailurePolicy == RequireOne)
					{
						return BH_FAILURE;
					}
				}
			}

			if (m_eFailurePolicy == RequireAll  &&  iFailureCount == m_Children.size())
			{
				return BH_FAILURE;
			}

			if (m_eSuccessPolicy == RequireAll  &&  iSuccessCount == m_Children.size())
			{
				return BH_SUCCESS;
			}

			return BH_RUNNING;
		}

		virtual void onTerminate(Status)
		{
			for (BTBehaviors::iterator it = m_Children.begin(); it != m_Children.end(); ++it)
			{
				BTBehavior& b = **it;
				if (b.isRunning())
				{
					b.abort();
				}
			}
		}
	};

	class CREAENGINE_API Monitor : public Parallel
	{
	public:
		Monitor()
			: Parallel(Parallel::RequireOne, Parallel::RequireOne)
		{
		}

		void addCondition(BTBehavior* condition)
		{
			m_Children.insert(m_Children.begin(), condition);
		}

		void addAction(BTBehavior* action)
		{
			m_Children.push_back(action);
		}
	};


	// ============================================================================

	class CREAENGINE_API ActiveSelector : public Selector
	{
	protected:

		virtual void onInitialize()
		{
			m_Current = m_Children.end();
		}

		virtual Status update()
		{
			BTBehaviors::iterator previous = m_Current;

			Selector::onInitialize();
			Status result = Selector::update();

			if (previous != m_Children.end() && m_Current != previous)
			{
				(*previous)->onTerminate(BH_ABORTED);
			}
			return result;
		}
	};

	class CREAENGINE_API SeekTo : public BTBehavior
	{
		Steering* m_pSteering;
		Seek* m_pSeek;
		float m_fArrivedDistance;

	public:
		SeekTo(Seek* _pSeek, float _fArrivedDistance)
			: m_fArrivedDistance(_fArrivedDistance)
		{
			m_pSeek = _pSeek;
			m_pSteering = m_pSeek->getEntity()->getComponent<Steering>();
		}

		virtual ~SeekTo()
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

			Vector2f targetOffset = m_pSeek->getTarget()->getPosition() - m_pSeek->getEntity()->getPosition();
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
	};

	class CREAENGINE_API FleeUntil : public BTBehavior
	{
		Steering* m_pSteering;
		Flee* m_pFlee;
		float m_fDistanceToFlee;

	public:
		FleeUntil(Flee* _pFlee, float _fDistanceToFlee)
			: m_fDistanceToFlee(_fDistanceToFlee)
		{
			m_pFlee = _pFlee;
			m_pSteering = m_pFlee->getEntity()->getComponent<Steering>();
		}

		virtual ~FleeUntil()
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

	};

	class CREAENGINE_API BTWander : public BTBehavior
	{
		Steering* m_pSteering;
		Wander* m_pWander;

	public:
		BTWander(Wander* _pWander)
		{
			m_pWander = _pWander;
			m_pSteering = m_pWander->getEntity()->getComponent<Steering>();
		}

		virtual ~BTWander()
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

	};

	class CREAENGINE_API IsAwayFromTarget : public Decorator
	{
		Entity* m_pEntity;
		Entity* m_pTarget;
		float m_fDistance;

	public:
		IsAwayFromTarget(Entity* _pEntity, Entity* _pTarget, float _fDistance)
		{
			m_pEntity = _pEntity;
			m_pTarget = _pTarget;
			m_fDistance = _fDistance;
		}

		virtual ~IsAwayFromTarget()
		{
		}

		virtual void onInitialize()
		{
		}

		virtual void onTerminate(Status s)
		{
			m_pChild->reset();
		}

		virtual Status update()
		{
			Vector2f targetOffset = m_pEntity->getPosition() - m_pTarget->getPosition();
			double distance = targetOffset.length();

			if (distance > m_fDistance)
			{
				m_pChild->tick();
				return m_pChild->getStatus();
			}
			else
			{
				m_pChild->abort();
				return BH_FAILURE;
			}
		}

	};

	class CREAENGINE_API Timer : public Decorator
	{
	public:
		Timer(BTBehavior* child)
			: Decorator(child)
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
			m_fTime += (float) frameTime.asSeconds();
			if (m_fTime >= m_fTimeLimit)
				return BH_SUCCESS;

			return m_pChild->tick();
		}

	protected:
		float m_fTimeLimit;
		float m_fTime;
	};

	class CREAENGINE_API EntityNameIs : public Decorator
	{
	public:
		EntityNameIs(Entity* _pEntity, string _szName)
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
			if (m_szName == m_pEntity->getName())
			{
				return BH_FAILURE;
			}
			
			return m_pChild->tick();
		}

	protected:
		string m_szName;
		Entity* m_pEntity;

	};
}

#endif //__BTBEHAVIOR_H_
