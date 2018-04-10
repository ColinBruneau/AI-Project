#include "stdafx.h"

#include "Scripts\CharacterController.h"
#include "Physics\Collider.h"
#include "Core\PhysicsManager.h"

namespace crea
{
	CharacterController::CharacterController()
	{
		m_pGM = GameManager::getSingleton();
		m_pActionTable = nullptr;
		m_pAnimator = nullptr;
		m_pCollider = nullptr;
	}

	CharacterController::~CharacterController()
	{
	}

	void CharacterController::setCollider(Collider* _pCollider)
	{
		m_pCollider = _pCollider;
	}

	void CharacterController::setActionTable(ActionTable* _pActionTable)
	{
		m_pActionTable = _pActionTable;
	}

	void CharacterController::setAnimator(Animator* _pAnimator)
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

	// Move the controller by a vector, only constrained by collisions
	void CharacterController::move(Vector2f _vMotion)
	{
		m_vVelocity = _vMotion;
	}

	bool CharacterController::init()
	{
		m_pActionTable = getEntity()->getComponent<ActionTable>();
		m_pAnimator = getEntity()->getComponent<Animator>();
		m_pCollider = getEntity()->getComponent<Collider>();

		m_bAlive = true;
		m_bMoving = false;
		m_eDirection = kADir_Down;
		m_eCondition = kACond_Default;
		m_eAction = kAct_Default;
		m_pCurrentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_eDirection, m_eCondition, m_eAction, nullptr));

		return true;
	}

	bool CharacterController::update()
	{
		// Preconditions
		if (!m_pCollider || !m_pAnimator || !m_pActionTable)
		{
			return false;
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
				//cout << fSpeedFactor << getEntity()->getPosition().getX() << " " << getEntity()->getPosition().getY() << endl;
			}
			//m_vVelocity *= fSpeedFactor;
			Vector2f vAdjustedVelocity = m_vVelocity * fSpeedFactor;
			Vector2f vAdjustedMotion = vAdjustedVelocity * (float)TimeManager::getSingleton()->getFrameTime().asSeconds();

			// Move
			m_pEntity->move(vAdjustedMotion);
			if (PhysicsManager::getSingleton()->isColliding(m_pCollider))
			{
				// Revert move
				m_pEntity->move(-vAdjustedMotion);
				m_vVelocity = Vector2f(0.f, 0.f);
			
				fSpeedFactor = 0;
			}
			// Adjust anim speed to velocity
			m_pCurrentAnimation->adjustToTranslationSpeed(vAdjustedVelocity.length());
		}

		// update AnimatedSprite
		m_pAnimator->update();

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
} // namespace crea
