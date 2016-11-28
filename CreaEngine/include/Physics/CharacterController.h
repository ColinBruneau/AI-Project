/***************************************************/
/* Nom:	CharacterController.h
/* Description: CharacterController
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __CharacterController_H_
#define __CharacterController_H_

#include "Core\Component.h"
#include "Core\ICore.h"
#include "Core\GameManager.h"

namespace crea
{
	enum EnumCharacterDirection
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
		kAct_Chop,
	};

	// Predefinitions
	class BoxCollider;
	class GameManager;

	class CREAENGINE_API CharacterController : public Component
	{
		GameManager* m_pGM;

		// Velocity
		float m_fSpeed;
		Vector2f m_vVelocity;

		// Collider
		Collider* m_pCollider;

		// Animation
		Animator* m_pAnimator;
		ActionTable* m_pActionTable;
		EnumCharacterDirection m_eDirection;
		EnumAnimCondition m_eCondition;
		EnumAction m_eAction;
		Animation* m_pCurrentAnimation;

		bool m_bAlive;
		bool m_bMoving;

		
	public:
		CharacterController();
		virtual ~CharacterController();

		void setCollider(Collider* _pCollider);
		void setActionTable(ActionTable* _pActionTable); // CB: check if possible to get as getComponent<ActionTable>()
		void setAnimator(Animator* _pAnimator);
		void setCondition(EnumAnimCondition _eCondition);	
		void setAction(EnumAction _eAction);
		void setDirection(EnumCharacterDirection _eDirection);
		void move(Vector2f _vMotion);
		
		virtual bool init();
		virtual bool update();
		virtual bool draw();
		virtual bool quit();
	};

} // namespace crea

#endif
