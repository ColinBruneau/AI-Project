/***************************************************/
/* Nom:	BehaviorTree.h
/* Description: BehaviorTree
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __BehaviorTree_H_
#define __BehaviorTree_H_

#include "Core\Component.h"
#include "Core\ICore.h"

namespace crea
{
	// Predefinitions
	class BTBehavior;

	class CREAENGINE_API BehaviorTree : public Component
	{
	protected:
		BTBehavior* m_pRoot;

	public:
		BehaviorTree();
		virtual ~BehaviorTree();

		void setRootBehavior(BTBehavior* _pRoot);

		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();
	};

} // namespace crea

#endif
