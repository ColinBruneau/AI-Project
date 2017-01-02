#include "stdafx.h"

#include "Core\GameManager.h"
#include "Core\TimeManager.h"

namespace crea
{
	GameManager::GameManager()
	{
		m_pRenderer = nullptr;
	}

	GameManager::~GameManager()
	{
		delete m_pRenderer;
	}

	GameManager* GameManager::getSingleton()
	{
		static GameManager instanceUnique;
		return
			&instanceUnique;
	}

	void GameManager::init()
	{
#ifdef _DIRECTX
#ifdef _DEBUG
		IFacade::load("CreaDirectX9-d.dll");
#else
		IFacade::load("CreaDirectX9.dll");
#endif
#else
#ifdef _DEBUG
		IFacade::load("CreaSFML-d.dll");
#else
		IFacade::load("CreaSFML.dll");
#endif
#endif
		m_pRenderer = &IFacade::get();

		m_pRenderer->initialize();

		TimeManager::getSingleton()->init();
	}

	void GameManager::update()
	{
		while (m_pRenderer->update())
		{
			// Time
			TimeManager::getSingleton()->update();

			// Input
			InputManager::getSingleton()->update();

			// Update
			SceneManager::getSingleton()->update();
			
			// Draw
			m_pRenderer->beginScene();

			SceneManager::getSingleton()->draw();

			m_pRenderer->endScene();
		}
	}

	void GameManager::quit()
	{
		m_pRenderer->quit();
	}


} // namespace crea
