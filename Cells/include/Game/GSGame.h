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

	Entity* m_pEntity1;
	ISprite* m_pSprite1;
	SpriteRenderer* m_pSpriteRenderer;

	Entity* m_pEntity2;
	ISprite* m_pSprite2;
	SpriteRenderer* m_pSpriteRenderer2;

	Clock frameClock;
	
	CharacterController* m_pCharacterController;
	ActionTable* m_pActionTable;
	Animator* m_pAnimator;
	UserController* m_pUserController;
	Collider* m_pCollider;

	Entity* m_pEntity3;
	Agent* m_pAgent;
	FSMPeon* m_pFSMPeon;

public:
	GSGame();
	virtual ~GSGame();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
