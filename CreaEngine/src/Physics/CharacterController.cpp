#include "stdafx.h"

#include "Physics\CharacterController.h"
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
		else if (m_eAction == kAct_Chop)
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
		m_fSpeed = 200.f; // CB: should be given by .cc file
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
			m_vVelocity.normalize();
			m_vVelocity *= m_fSpeed * (float)TimeManager::getSingleton()->getFrameTime().asSeconds();

			// Friction
			Map* pMap = PhysicsManager::getSingleton()->getCurrentMap();
			float fSpeedFactor = 1 - pMap->getFrictionAtPosition(this->getEntity()->getPosition());
			m_vVelocity *= fSpeedFactor;

			// Move
			m_pEntity->move(m_vVelocity);
			
			if (PhysicsManager::getSingleton()->isColliding(m_pCollider))
			{
				// Revert move
				m_pEntity->move(-m_vVelocity);
				m_vVelocity = Vector2f(0.f, 0.f);
				fSpeedFactor = 0;
			}

			// Adjust anim speed to velocity
			m_pCurrentAnimation->adjustToTranslationSpeed(m_fSpeed*fSpeedFactor);
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
