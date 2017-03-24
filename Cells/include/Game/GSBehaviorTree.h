/***************************************************/
/* Nom:	GSBehaviorTree.h
/* Description: GSBehaviorTree
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __GSBehaviorTree_H_
#define __GSBehaviorTree_H_

#include "Core\GameState.h"
#include "AI\BehaviorTree\BTBehavior.h"

using namespace crea;

class GSBehaviorTree : public crea::GameState
{
	GameManager*	m_pGM;

	IText* m_pTextFPS;
	Clock frameClock;

	IText* m_pTextBTMode;
	int m_iBTMode;

	// Entitites
	int m_iNbEntities;
	vector<Entity*> m_vEntities;
	bool m_bKeyPressedAdd;
	bool m_bKeyPressedSub;

	// Obstacles
	vector<Entity*> m_vObstacles;

	Entity* m_pMouse;

	IntRect m_rWindowRect;
	
public:
	GSBehaviorTree();
	virtual ~GSBehaviorTree();

	void deleteEntities();
	void createEntities(); 
	void setBehavior();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
