/***************************************************/
/* Nom:	StateGame.h
/* Description: StateGame
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __StateGame_H_
#define __StateGame_H_

#include "Core\State.h"
#include "AI\ActionTable.h"
#include "Physics\CharacterController.h"
#include "Input\UserController.h"
#include "Physics\Collider.h"

using namespace crea;



class StateGame : public crea::State
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

public:
	StateGame();
	virtual ~StateGame();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
