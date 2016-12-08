#include "stdafx.h"

#include "Core\SceneManager.h"
#include "Core\GameState.h"
#include "Core\PhysicsManager.h"

namespace crea
{
	SceneManager::SceneManager()
	{
		m_pCurrentGameState = nullptr;
	}

	SceneManager::~SceneManager()
	{
		if (m_pCurrentGameState)
		{
			m_pCurrentGameState->onQuit();
			delete m_pCurrentGameState;
		}
	}

	SceneManager* SceneManager::getSingleton()
	{
		static SceneManager instanceUnique;
		return
			&instanceUnique;
	}
	
	bool SceneManager::update()
	{
		EntityManager::getSingleton()->update();
		if (m_pCurrentGameState)
			return m_pCurrentGameState->onUpdate();
		return false;
	}

	bool SceneManager::draw()
	{
		EntityManager::getSingleton()->draw();

		// CB: add a flag to draw or not
		PhysicsManager::getSingleton()->draw();

		if (m_pCurrentGameState)
			return m_pCurrentGameState->onDraw();
		return false;
	}

	void SceneManager::setGameState(GameState* _s)
	{
		if (m_pCurrentGameState)
		{
			m_pCurrentGameState->onQuit();
			EntityManager::getSingleton()->clear();
			PhysicsManager::getSingleton()->clear();
			delete m_pCurrentGameState;
		}
		m_pCurrentGameState = _s;
		m_pCurrentGameState->onInit();
		EntityManager::getSingleton()->init();
		PhysicsManager::getSingleton()->init();
	}


} // namespace crea
