/***************************************************/
/* Nom:	GSSteering.h
/* Description: GSSteering
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __GSSteering_H_
#define __GSSteering_H_

#include "Core\GameState.h"

using namespace crea;

class GSSteering : public crea::GameState
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

	Entity* m_pMouse;

	IntRect m_rWindowRect;

public:
	GSSteering();
	virtual ~GSSteering();

	void deleteEntities();
	void createEntities(); 
	void setBehavior();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
