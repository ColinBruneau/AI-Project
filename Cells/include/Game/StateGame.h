/***************************************************/
/* Nom:	StateGame.h
/* Description: StateGame
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __StateGame_H_
#define __StateGame_H_

#include "Core\State.h"
#include "AI\ActionTable.h"

enum EnumAnimCondition
{
	kACond_Invalid = -1,
	kACond_Default = 0,
	kACond_Up,
	kACond_Right,
	kACond_Down,
	kACond_Left,
};

enum EnumAction
{
	kAct_Invalid = -1,
	kAct_Default = 0,
	kAct_Idle,
	kAct_Walk,
};

class StateGame : public crea::State
{
	crea::GameManager*	m_pGM;

	crea::IText* m_pTextFPS;

	crea::Entity* m_pEntity1;
	crea::ISprite* m_pSprite1;
	crea::SpriteRenderer* m_pSpriteRenderer;

	crea::Entity* m_pEntity2;
	crea::AnimatedSprite* m_pAnimatedSprite1;
	crea::AnimatedSpriteRenderer* m_pAnimatedSpriteRenderer;
	crea::Animation walkingAnimationDown;
	crea::Animation walkingAnimationLeft;
	crea::Animation walkingAnimationRight;
	crea::Animation walkingAnimationUp;
	crea::Animation* currentAnimation;

	crea::Clock frameClock;
	float speed;
	bool noKeyWasPressed;

	crea::ActionTable* m_pActionTable;

public:
	StateGame();
	virtual ~StateGame();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
