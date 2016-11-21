/***************************************************/
/* Nom:	StateGame.h
/* Description: StateGame
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __StateGame_H_
#define __StateGame_H_

#include "Core\State.h"
#include "AI\ActionTable.h"

enum EnumAnimDirection
{
	kADir_Invalid = -1,
	kADir_Up,
	kADir_UpRight,
	kADir_Right,
	kADir_DownRight,
	kADir_Down,
	kADir_DownLeft,
	kADir_Left,
	kADir_UpLeft,
};

enum EnumAnimCondition
{
	kACond_Invalid = -1,
	kACond_Default = 0,
	kACond_Lumber,
	kACond_Gold,
};

enum EnumAction
{
	kAct_Invalid = -1,
	kAct_Default = 0,
	kAct_Idle,
	kAct_Walk,
	kAct_Die,
};

class StateGame : public crea::State
{
	crea::GameManager*	m_pGM;

	crea::IText* m_pTextFPS;

	crea::Entity* m_pEntity1;
	crea::ISprite* m_pSprite1;
	crea::SpriteRenderer* m_pSpriteRenderer;

	crea::Entity* m_pEntity2;
	crea::ISprite* m_pSprite2;
	crea::SpriteRenderer* m_pSpriteRenderer2;
	crea::Animator* m_pAnimator;
	crea::Animation* currentAnimation;

	crea::Clock frameClock;
	float speed;
	bool noKeyWasPressed;

	crea::ActionTable* m_pActionTable;
	EnumAnimDirection m_CurrentDirection;
	EnumAnimCondition m_CurrentCondition;
	bool m_bAlive;

public:
	StateGame();
	virtual ~StateGame();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
