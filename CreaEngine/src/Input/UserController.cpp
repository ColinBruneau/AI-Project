#include "stdafx.h"

#include "Input\UserController.h"

namespace crea
{
	// UserController
	UserController::UserController()
	{
		m_pCharacterController = nullptr;
		m_pGM = GameManager::getSingleton();
	}

	UserController::~UserController()
	{
	}

	void UserController::setCharacterController(CharacterController* _pCharacterController)
	{ 
		m_pCharacterController = _pCharacterController; 
	}

	bool UserController::init()
	{
		return true;
	}

	bool UserController::update()
	{
		// Preconditions
		if (!m_pCharacterController)
		{
			return false;
		}

		// Conditions
		if (m_pGM->isKeyPressed(Key::D))
		{
			m_pCharacterController->setCondition(kACond_Default);
		}

		if (m_pGM->isKeyPressed(Key::G))
		{
			m_pCharacterController->setCondition(kACond_Gold);
		}

		if (m_pGM->isKeyPressed(Key::L))
		{
			m_pCharacterController->setCondition(kACond_Lumber);
		}

		// Actions
		if (m_pGM->isKeyPressed(Key::C))
		{
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Chop);
		}

		if (m_pGM->isKeyPressed(Key::K))
		{
			m_pCharacterController->setCondition(kACond_Default);
			m_pCharacterController->setAction(kAct_Die);
		}
		else
		{
			m_pCharacterController->setAction(kAct_Default);
		}

		// Directions
		m_vVelocity = Vector2f(0.f, 0.0f);
		if (m_pGM->isKeyPressed(Key::Up))
		{
			m_vVelocity = Vector2f(0.f, -1.0f);
			m_pCharacterController->setDirection(kADir_Up);
			m_pCharacterController->setAction(kAct_Walk);
		}
		if (m_pGM->isKeyPressed(Key::Down))
		{
			m_vVelocity = Vector2f(0.f, 1.0f);
			m_pCharacterController->setDirection(kADir_Down);
			m_pCharacterController->setAction(kAct_Walk);
		}
		if (m_pGM->isKeyPressed(Key::Left))
		{
			m_vVelocity = Vector2f(-1.f, 0.0f);
			m_pCharacterController->setDirection(kADir_Left);
			m_pCharacterController->setAction(kAct_Walk);
		}
		if (m_pGM->isKeyPressed(Key::Right))
		{
			m_vVelocity = Vector2f(1.f, 0.0f);
			m_pCharacterController->setDirection(kADir_Right);
			m_pCharacterController->setAction(kAct_Walk);
		}
		if (m_pGM->isKeyPressed(Key::Up) && m_pGM->isKeyPressed(Key::Right))
		{
			m_vVelocity = Vector2f(1.f, -1.0f);
			m_pCharacterController->setDirection(kADir_UpRight);
			m_pCharacterController->setAction(kAct_Walk);
		}
		if (m_pGM->isKeyPressed(Key::Up) && m_pGM->isKeyPressed(Key::Left))
		{
			m_vVelocity = Vector2f(-1.f, -1.0f);
			m_pCharacterController->setDirection(kADir_UpLeft);
			m_pCharacterController->setAction(kAct_Walk);
		}
		if (m_pGM->isKeyPressed(Key::Down) && m_pGM->isKeyPressed(Key::Right))
		{
			m_vVelocity = Vector2f(1.f, 1.0f);
			m_pCharacterController->setDirection(kADir_DownRight);
			m_pCharacterController->setAction(kAct_Walk);
		}
		if (m_pGM->isKeyPressed(Key::Down) && m_pGM->isKeyPressed(Key::Left))
		{
			m_vVelocity = Vector2f(-1.f, 1.0f);
			m_pCharacterController->setDirection(kADir_DownLeft);
			m_pCharacterController->setAction(kAct_Walk);
		}

		m_vVelocity.normalize();
		m_pCharacterController->move(m_vVelocity * (float)TimeManager::getSingleton()->getFrameTime().asSeconds());

		return true;
	}

	bool UserController::draw()
	{
		return true;
	}

	bool UserController::quit()
	{
		return true;
	}

	// KeyboardUserController
	KeyboardUserController::KeyboardUserController()
	{
	}

	KeyboardUserController::~KeyboardUserController()
	{
	}

	bool KeyboardUserController::init()
	{
		return true;
	}

	bool KeyboardUserController::update()
	{
		return true;
	}

	bool KeyboardUserController::draw()
	{
		return true;
	}

	bool KeyboardUserController::quit()
	{
		return true;
	}
} // namespace crea
