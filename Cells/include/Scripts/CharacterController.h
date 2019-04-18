/***************************************************/
/* Nom:	CharacterController.h
/* Description: CharacterController
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __CharacterController_H_
#define __CharacterController_H_

#include "Core\Script.h"
#include "Core\Math.h"
#include "Core\GameManager.h"
using namespace crea;

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

class CharacterController : public crea::Script
{
	GameManager* m_pGM;
	Agent* m_pAgent;
	Vehicle* m_pVehicle;

	// Velocity
	Vector2f m_vMotion;
	float m_fVelocityMax;

	// Animation
	Animator* m_pAnimator;
	ActionTable* m_pActionTable;
	EnumCharacterDirection m_eDirection;
	EnumAnimCondition m_eCondition;
	EnumAction m_eAction;
	Animation* m_pCurrentAnimation;

	bool m_bAlive;
	bool m_bMoving;

	bool shouldFollowPath = false;
	vector<Vector2f*> m_path;
	vector<Vector2f*>::iterator m_previousIt;
	vector<Vector2f*>::iterator m_nextIt;
	Vector2f m_offset;

	// Collider
	Collider* m_pCollider;
	bool m_isColliding = false;

public:
	CharacterController();
	virtual ~CharacterController();

	void setActionTable(ActionTable* _pActionTable);
	void setAnimator(Animator* _pAnimator);

	void setCondition(EnumAnimCondition _eCondition);
	void setAction(EnumAction _eAction);
	void setDirection(EnumCharacterDirection _eDirection);

	void setDirection(Vector2f _vDirection);

	EnumAnimCondition getCondition() { return m_eCondition; }
	EnumAction getAction() { return m_eAction; }
	EnumCharacterDirection getDirection() { return m_eDirection; }

	void move(Vector2f _vMotion);
	void followPath(vector<Vector2f*>& _path, const Vector2f& _offset = Vector2f(0.f, 0.f));
	bool stupidSwordman(Vector2f& _position, Vector2f& _direction, float _speed);
	inline bool isFollowingPath() { return shouldFollowPath; }
	inline void setFollowingPath(bool _bFollowingPath) { shouldFollowPath = _bFollowingPath; }
	virtual bool init();
	virtual bool update();
	virtual bool draw();
	virtual bool quit();

	virtual void onCollisionEnter2D(Collision2D& _coll);
	virtual void onCollisionExit2D(Collision2D& _coll);

	virtual Component* clone() { return new CharacterController(*this); }
};


#endif
