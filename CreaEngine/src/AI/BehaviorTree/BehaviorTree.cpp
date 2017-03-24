#include "stdafx.h"

#include "AI\BehaviorTree\BehaviorTree.h"
#include "AI\BehaviorTree\BTBehavior.h"

namespace crea
{
	BehaviorTree::BehaviorTree()
		: m_pRoot(nullptr)
	{
	}

	BehaviorTree::~BehaviorTree()
	{
	}

	void BehaviorTree::setRootBehavior(BTBehavior* _pRoot)
	{
		m_pRoot = _pRoot;
	}

	bool BehaviorTree::init()
	{
		return true;
	}

	bool BehaviorTree::update()
	{
		if (m_pRoot)
		{
			m_pRoot->tick();
			return true;
		}
		return false;
	}

	bool BehaviorTree::draw()
	{
	
		return true;
	}

	bool BehaviorTree::quit()
	{
		return true;
	}
} // namespace crea
