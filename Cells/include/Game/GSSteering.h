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

	Entity* m_pMouse;

public:
	GSSteering();
	virtual ~GSSteering();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
