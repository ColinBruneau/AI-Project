/***************************************************/
/* Nom:	GSGame.h
/* Description: GSGame
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __GSGame_H_
#define __GSGame_H_

#include "Core\GameState.h"
#include "AI\ActionTable.h"
#include "Physics\CharacterController.h"
#include "Input\UserController.h"
#include "Physics\Collider.h"

#include "FSMPeon.h"

using namespace crea;

class GSGame : public crea::GameState
{
	GameManager*	m_pGM;

	IText* m_pTextFPS;

	Agent* m_pAgent1;
	FSMPeon* m_pFSMPeon1;

	Agent* m_pAgent2;
	FSMPeon* m_pFSMPeon2;

	Clock frameClock;

	Entity* m_pEntity3;

	// Selection
	bool m_bSelection;
	Vector2f m_vStartSelection;
	Vector2f m_vEndSelection;

public:
	GSGame();
	virtual ~GSGame();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
