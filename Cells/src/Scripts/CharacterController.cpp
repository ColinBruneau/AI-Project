#include "stdafx.h"

#include "Scripts\CharacterController.h"


CharacterController::CharacterController()
{
	m_pGM = crea::GameManager::getSingleton();
	m_pActionTable = nullptr;
	m_pAnimator = nullptr;
	m_pCollider = nullptr;
}

CharacterController::~CharacterController()
{
}

void CharacterController::setActionTable(crea::ActionTable* _pActionTable)
{
	m_pActionTable = _pActionTable;
}

void CharacterController::setAnimator(crea::Animator* _pAnimator)
{
	m_pAnimator = _pAnimator;
}

void CharacterController::setCondition(EnumAnimCondition _eCondition)
{
	m_eCondition = _eCondition;
}

void CharacterController::setAction(EnumAction _eAction)
{
	m_eAction = _eAction;

	// CB: should be given by the action table or the animation?
	if (m_eAction == kAct_Die)
	{
		m_bAlive = false;
		m_bMoving = false;
	}
	else if (m_eAction == kAct_Chop) // CB: Not sure Chop should be in engine... Static instead?
	{
		m_bAlive = true;
		m_bMoving = false;
	}
	else
	{
		m_bAlive = true;
		m_bMoving = true;
	}
}

void CharacterController::setDirection(EnumCharacterDirection _eDirection)
{
	m_eDirection = _eDirection;
}

void CharacterController::setDirection(Vector2f _vDirection)
{
	int iDirection = 0;
	Vector2f vRight(0.f, -1.f);
	float fAngle = vRight.angle(_vDirection);
	if (_vDirection.getX() > 0)
	{
		iDirection = (int)(0.5f + fAngle * 4 / 3.14f);
		setDirection((EnumCharacterDirection)iDirection);
	}
	else
	{
		iDirection = 8 - (int)(0.5f + fAngle * 4 / 3.14f);
		iDirection = (iDirection == 8) ? 0 : iDirection;
		setDirection((EnumCharacterDirection)iDirection);
	}
	m_pEntity->setOrientation(_vDirection);
}

// Move the controller by a vector, only constrained by collisions
void CharacterController::move(crea::Vector2f _vMotion)
{
	m_vMotion = _vMotion;
}

void CharacterController::followPath(vector<Vector2f*>& _path, const Vector2f& _offset)
{
	m_path.clear();
	m_path.assign(_path.begin(), _path.end());
	m_nextIt = m_path.end();
	shouldFollowPath = true;
	m_offset = _offset;
}

bool CharacterController::stupidSwordman(Vector2f& _position, Vector2f& _direction, float _speed)
{
	bool isEndOfPath = true;
	if (m_nextIt == m_path.end())
	{
		m_previousIt = m_nextIt = m_path.begin();
	}
	float distance = _speed * (float)crea::TimeManager::getSingleton()->getFrameTime().asSeconds();
	_direction = **m_nextIt - _position;
	while (m_nextIt != m_path.end() && _direction.length() < distance)
	{
		distance -= _direction.length();
		m_previousIt = m_nextIt;
		m_nextIt++;
		if (m_nextIt != m_path.end())
		{
			_direction = **m_nextIt - **m_previousIt;
			_position = **m_previousIt;
		}
		else
		{
			_direction = Vector2f(0.f, 0.f);
			isEndOfPath = false;
		}
	}
	if (m_nextIt != m_path.end())
	{
		_direction.normalize();
		_position += _direction * distance;
	}
	return isEndOfPath;
}

bool CharacterController::init()
{
	m_pActionTable = getEntity()->getComponent<crea::ActionTable>();
	m_pAnimator = getEntity()->getComponent<crea::Animator>();
	m_pCollider = getEntity()->getComponent<Collider>();
	m_pAgent = m_pEntity->getComponent<Agent>();
	m_pVehicle = m_pEntity->getComponent<Vehicle>();

	m_bAlive = true;
	m_bMoving = false;
	m_eDirection = kADir_Down;
	m_eCondition = kACond_Default;
	m_eAction = kAct_Default;
	m_pCurrentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_eDirection, m_eCondition, m_eAction, nullptr));

	m_fVelocityMax = 100.f;

	return true;
}

bool CharacterController::update()
{
	// Preconditions
	if (!m_pCollider || !m_pAnimator || !m_pActionTable)
	{
		return false;
	}

	if (shouldFollowPath)
	{
		// Stupid swordman algorithm
		Vector2f position = m_pEntity->getPosition();
		shouldFollowPath = stupidSwordman(position, m_vMotion, m_fVelocityMax);
		m_vMotion *= m_fVelocityMax; 
		setDirection(m_vMotion);
		setAction(kAct_Walk);
	}

	m_pCurrentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_eDirection, m_eCondition, m_eAction));
	m_pAnimator->play(*m_pCurrentAnimation);
	m_pCurrentAnimation->setSpeed(1.0f); // Play full speed by default

	if (m_bMoving)
	{
		// Friction
		float fSpeedFactor = 1.f;
		Map* pCurrentMap = PhysicsManager::getSingleton()->getCurrentMap();
		if (pCurrentMap)
		{
			fSpeedFactor = 1 - pCurrentMap->getFrictionAtPosition(getEntity()->getPosition());
		}

		// Move
		float speed = min(m_vMotion.length(), m_fVelocityMax);
		m_vMotion.normalize();
		m_vMotion *= (speed * m_pAgent->getDexterity()*0.1f);
		Vector2f vAdjustedMotion = m_vMotion * fSpeedFactor;
		m_pEntity->move(vAdjustedMotion * (float)crea::TimeManager::getSingleton()->getFrameTime().asSeconds());

		// Collision

		// // Todo: à vérifier pourquoi on ne décolle pas avec le booléen
		//if (m_isColliding)
		/*if (PhysicsManager::getSingleton()->isColliding(m_pCollider))
		{
		// Revert move
		m_pEntity->move(-vAdjustedMotion * (float)crea::TimeManager::getSingleton()->getFrameTime().asSeconds());
		m_vMotion = vAdjustedMotion = Vector2f(0.f, 0.f);
		m_eAction = kAct_Idle;
		}*/

		// Adjust anim speed to velocity
		// Todo: Translationspeed should be adjusted in Animator, not Animation 
		// because an animation is shared between instances, not Animator
		m_pCurrentAnimation->adjustToTranslationSpeed(2 * vAdjustedMotion.length());
	}

	// update AnimatedSprite
	//m_pAnimator->update();

	return true;
}

bool CharacterController::draw()
{
	return true;
}

bool CharacterController::quit()
{
	return true;
}

void CharacterController::onCollisionEnter2D(Collision2D& _coll)
{
	m_isColliding = true;
	return;
}

void CharacterController::onCollisionExit2D(Collision2D& _coll)
{
	m_isColliding = false;
	return;
}
