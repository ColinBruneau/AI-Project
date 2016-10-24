/***************************************************/
/* Nom:	StateMenu.h
/* Description: StateMenu
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __StateMenu_H_
#define __StateMenu_H_

#include "Core\State.h"

class StateMenu : public crea::State
{
	crea::GameManager*	m_pGM;

public:
	StateMenu();
	virtual ~StateMenu();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
