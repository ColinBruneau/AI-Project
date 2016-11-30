#include "stdafx.h"

#include "Core\SceneManager.h"
#include "Core\State.h"
#include "Core\PhysicsManager.h"

namespace crea
{
	SceneManager::SceneManager()
	{
		m_pCurrentState = nullptr;
	}

	SceneManager::~SceneManager()
	{
		if (m_pCurrentState)
		{
			m_pCurrentState->onQuit();
			delete m_pCurrentState;
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
		if (m_pCurrentState)
			return m_pCurrentState->onUpdate();
		return false;
	}

	bool SceneManager::draw()
	{
		EntityManager::getSingleton()->draw();

		// CB: add a flag to draw or not
		PhysicsManager::getSingleton()->draw();

		if (m_pCurrentState)
			return m_pCurrentState->onDraw();
		return false;
	}

	void SceneManager::setState(State* _s)
	{
		if (m_pCurrentState)
		{
			m_pCurrentState->onQuit();
			EntityManager::getSingleton()->clear();
			PhysicsManager::getSingleton()->clear();
			delete m_pCurrentState;
		}
		m_pCurrentState = _s;
		m_pCurrentState->onInit();
		EntityManager::getSingleton()->init();
		PhysicsManager::getSingleton()->init();
	}


} // namespace crea
