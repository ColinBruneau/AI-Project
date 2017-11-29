#include "stdafx.h"

#include "Scene\SceneMap.h"
#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"
#include "Scene\SceneFormation.h"
#include "Scene\SceneSteering.h"
#include "Scene\SceneBehaviorTree.h"


SceneMap::SceneMap()
{
	// AI Tools
	m_bUseAITools = true;
	m_pAITools = new AITools;
}

SceneMap::~SceneMap()
{
	// AI Tools
	delete m_pAITools;
}
	
bool SceneMap::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Set Script factory
	m_pCellsScriptFactory = new CellsScriptFactory;
	m_pGM->setScriptFactory(m_pCellsScriptFactory);

	// Load Map
	m_pEntity3 = m_pGM->getEntity("map1");
	m_pGM->addEntity(m_pEntity3);
	m_pMap = m_pGM->getMap("map1.json"); // CB: TO CHANGE: map id loaded after entity added to display map first (order in tree matters)
	m_pMapRenderer = m_pGM->getMapRenderer("MapRenderer1");
	m_pMapRenderer->setMap(m_pMap);
	m_pEntity3->addComponent(m_pMapRenderer);

	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->setCurrentMap(m_pMap);
		m_pAITools->onInit();
	}
	return true;
}

bool SceneMap::onUpdate()
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

	// Collision
	if (m_pGM->isKeyPressed(Key::C))
	{
		m_pMap->setDisplayCollision(true);
	}
	else
	{
		m_pMap->setDisplayCollision(false);
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

bool SceneMap::onDraw()
{
	if (m_bUseAITools)
	{
		m_pAITools->onDraw();
	}
	return true;
}

bool SceneMap::onQuit()
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

