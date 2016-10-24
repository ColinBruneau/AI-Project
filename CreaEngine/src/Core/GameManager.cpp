#include "stdafx.h"

#include "Core\GameManager.h"

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
		// Chargement du renderer DirectX9
		//IRenderer::Load(""CreaDirectX9.dll");
#ifdef _DEBUG
		IRenderer::load("CreaSFML-d.dll");
#else
		IRenderer::load("CreaSFML.dll");
#endif
		m_pRenderer = &IRenderer::get();

		m_pRenderer->initialize();
	}

	void GameManager::update()
	{
		while (m_pRenderer->update())
		{
			// Time

			// Input
			InputManager::getSingleton()->update();

			// Update
			SceneManager::getSingleton()->update();
			EntityManager::getSingleton()->update();

			// Draw
			m_pRenderer->beginScene();

			SceneManager::getSingleton()->draw();
			EntityManager::getSingleton()->draw();

			m_pRenderer->endScene();
		}
	}

	void GameManager::quit()
	{
		m_pRenderer->quit();
	}


} // namespace crea