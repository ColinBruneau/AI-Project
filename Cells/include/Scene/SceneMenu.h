/***************************************************/
/* Nom:	SceneMenu.h
/* Description: SceneMenu
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __SceneMenu_H_
#define __SceneMenu_H_

#include "Core\Scene.h"

using namespace crea;

class SceneMenu : public Scene
{
	GameManager*	m_pGM;

public:
	SceneMenu();
	virtual ~SceneMenu();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
