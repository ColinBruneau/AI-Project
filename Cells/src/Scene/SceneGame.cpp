#include "stdafx.h"

#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"
#include "Scene\SceneMap.h"
#include "Scene\SceneFormation.h"
#include "Scene\SceneSteering.h"
#include "Scene\SceneBehaviorTree.h"
#include "Core\SceneManager.h"
#include "Core\Math.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\ISprite.h"
#include "Core\TimeManager.h"
#include "AI\StateMachine.h"
#include "AI\Pathfinding\MapSearchManager.h"


SceneGame::SceneGame()
{
	// AI Tools
	m_bUseAITools = true;
	m_pAITools = new AITools;
}

SceneGame::~SceneGame()
{
	// AI Tools
	delete m_pAITools;
}
	
bool SceneGame::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Set Script factory
	m_pCellsScriptFactory = new CellsScriptFactory;
	m_pGM->setScriptFactory(m_pCellsScriptFactory);

	// Load Map
	Entity* m_pEntity3;
	Map* m_pMap;
	MapRenderer* m_pMapRenderer;
	m_pEntity3 = m_pGM->getEntity("map1");
	m_pGM->addEntity(m_pEntity3);
	m_pMap = m_pGM->getMap("map1.json"); // CB: TO CHANGE: map id loaded after entity added to display map first (order in tree matters)
	m_pMapRenderer = m_pGM->getMapRenderer("MapRenderer1");
	m_pMapRenderer->setMap(m_pMap);
	m_pEntity3->addComponent(m_pMapRenderer);

	// Set Map as pathfinding space
	MapSearchManager::getSingleton()->setMap(m_pMap);


	// Entity 1
	m_pAgent1 = m_pGM->getAgent("Peon/Peon1.chr");
	m_pFSMPeon1 = new FSMPeon(m_pAgent1);
	m_pAgent1->SetStateMachine(m_pFSMPeon1); // CB: can't we just call SetStateMachine in FSMPeon?

	
	// Entity 2
	//m_pAgent2 = m_pGM->getAgent("Peon/Peon2.chr");
	//m_pFSMPeon2 = new FSMPeon(m_pAgent2);
	//m_pAgent2->SetStateMachine(m_pFSMPeon2); // CB: can't we just call SetStateMachine in FSMPeon?

	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->setCurrentMap(m_pMap);
		m_pAITools->onInit();
	}

	return true;
}

bool SceneGame::onUpdate()
{
	if (m_pGM->isKeyPressed(Key::Num1))
	{
		m_pGM->setScene(new SceneMenu());
		return true;
	}
	if (m_pGM->isKeyPressed(Key::Num2))
	{
		m_pGM->setScene(new SceneGame());
		return true;
	}
	if (m_pGM->isKeyPressed(Key::Num3))
	{
		m_pGM->setScene(new SceneSteering());
		return true;
	}
	if (m_pGM->isKeyPressed(Key::Num4))
	{
		m_pGM->setScene(new SceneFormation());
		return true;
	}
	if (m_pGM->isKeyPressed(Key::Num5))
	{
		m_pGM->setScene(new SceneBehaviorTree());
		return true;
	}

	// AI Tools
	if (m_pGM->isKeyPressed(Key::F12))
	{
		m_bUseAITools = !m_bUseAITools;
	}
	if (m_bUseAITools)
	{
		m_pAITools->onUpdate();
	}
	return true;
}

bool SceneGame::onDraw()
{
	if (m_bUseAITools)
	{
		m_pAITools->onDraw();
	}
	return true;
}

bool SceneGame::onQuit()
{	
	if (m_bUseAITools)
	{
		m_pAITools->onQuit();
	}

	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	delete m_pCellsScriptFactory;
	m_pGM->setScriptFactory(nullptr);

	return true;
}

