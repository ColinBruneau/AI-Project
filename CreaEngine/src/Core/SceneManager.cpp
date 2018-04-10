#include "stdafx.h"

#include "Core\SceneManager.h"
#include "Core\Scene.h"
#include "Core\PhysicsManager.h"

namespace crea
{
	SceneManager::SceneManager()
	{
		m_pCurrentScene = nullptr;
	}

	SceneManager::~SceneManager()
	{
		if (m_pCurrentScene)
		{
			m_pCurrentScene->onQuit();
			delete m_pCurrentScene;
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
		MsgManager::getSingleton()->update();
		EntityManager::getSingleton()->update();
		if (m_pCurrentScene)
			return m_pCurrentScene->onUpdate();
		return false;
	}

	bool SceneManager::draw()
	{
		EntityManager::getSingleton()->draw();

		// CB: add a flag to draw or not
		PhysicsManager::getSingleton()->draw();

		if (m_pCurrentScene)
			return m_pCurrentScene->onDraw();
		return false;
	}

	void SceneManager::setScene(Scene* _s)
	{
		if (m_pCurrentScene)
		{
			m_pCurrentScene->onQuit();
			EntityManager::getSingleton()->clear();
			PhysicsManager::getSingleton()->clear();
			delete m_pCurrentScene;
		}
		m_pCurrentScene = _s;
		m_pCurrentScene->onInit();
		EntityManager::getSingleton()->init();
		PhysicsManager::getSingleton()->init();
	}


} // namespace crea
