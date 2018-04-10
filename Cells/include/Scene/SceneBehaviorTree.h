/***************************************************/
/* Nom:	SceneBehaviorTree.h
/* Description: SceneBehaviorTree
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __SceneBehaviorTree_H_
#define __SceneBehaviorTree_H_

#include "Core\Scene.h"
#include "AI\BehaviorTree\BTBehavior.h"

using namespace crea;

class SceneBehaviorTree : public crea::Scene
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
	SceneBehaviorTree();
	virtual ~SceneBehaviorTree();

	void deleteEntities();
	void createEntities(); 
	void setBehavior();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
