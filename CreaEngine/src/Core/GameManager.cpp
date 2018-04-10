#include "stdafx.h"

#include "Core\GameManager.h"
#include "Core\TimeManager.h"
#include "Tools\Logger.h"

namespace crea
{
	GameManager::GameManager()
	{
		m_pRenderer = nullptr;
	}

	GameManager::~GameManager()
	{
		// Do not delete renderer as it will be deleted on it's own (or before GameManager...)
		//delete m_pRenderer;

	}

	GameManager* GameManager::getSingleton()
	{
		static GameManager instanceUnique;
		return
			&instanceUnique;
	}

	void GameManager::init()
	{
		m_pLogger = new LoggerFile("CreaEngine.log");
		ILogger::SetLogger(m_pLogger);
		ILogger::Log("GameManager::init()\n");

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
		ILogger::Log("GameManager::quit()\n");
		m_pRenderer->quit();
		delete m_pLogger;
	}


} // namespace crea
