/***************************************************/
/* Nom:	GSFormation.h
/* Description: GSFormation
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __GSFormation_H_
#define __GSFormation_H_

#include "Core\GameState.h"

using namespace crea;

class GSFormation : public crea::GameState
{
	GameManager*	m_pGM;

	IText* m_pTextFPS;
	Clock frameClock;

	IText* m_pTextSteeringMode;
	int m_iSteeringMode;

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
	GSFormation();
	virtual ~GSFormation();

	void deleteEntities();
	void createEntities(); 
	void setBehavior();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
