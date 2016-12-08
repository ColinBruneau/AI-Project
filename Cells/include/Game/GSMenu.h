/***************************************************/
/* Nom:	GSMenu.h
/* Description: GSMenu
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __GSMenu_H_
#define __GSMenu_H_

#include "Core\GameState.h"

using namespace crea;

class GSMenu : public GameState
{
	GameManager*	m_pGM;

public:
	GSMenu();
	virtual ~GSMenu();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
