#include "stdafx.h"

#include "Scene\ScenePlanning.h"
#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"
#include "Scene\SceneMap.h"
#include "Scene\SceneSteering.h"
#include "AI\Steering\Behavior.h"
#include <string>

ScenePlanning::ScenePlanning()
{
	// AI Tools
	m_bUseAITools = true;
	m_pAITools = new AITools();
}

ScenePlanning::~ScenePlanning()
{
	// AI Tools
	delete m_pAITools;
}

bool ScenePlanning::onInit()
{
	m_pGM = GameManager::getSingleton();
	m_rWindowRect = m_pGM->getWindowRect();

	// Set Script factory
	m_pCellsScriptFactory = new CellsScriptFactory;
	m_pGM->setScriptFactory(m_pCellsScriptFactory);

	// Load Map
	m_pEntity4 = m_pGM->getEntity("MapPlanning");
	m_pGM->addEntity(m_pEntity4);
	m_pMap = m_pGM->getMap("MapPlanning.json"); // CB: TO CHANGE: Map id loaded after entity added to display Map first (order in tree matters)
	m_pMap->loadFromFileJSON(string(DATAMAPPATH) + "MapPlanning.json");
	m_pMapRenderer = m_pGM->getMapRenderer("MapRenderer1");
	m_pMapRenderer->setMap(m_pMap);
	m_pEntity4->addComponent(m_pMapRenderer);

	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onInit();
	}

	// TD BT
	Blackboard* pBB = Blackboard::getSingleton();
	pBB->setVariable("HqHaveGold", "0");
	pBB->setVariable("HqHaveFirewood", "0");
	pBB->setVariable("HqHaveTool", "0");
	pBB->setVariable("HqHaveLogs", "0");
	pBB->setVariable("HqHaveMoreGold", "0");

	return true;
}

bool ScenePlanning::onUpdate()
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
		m_pGM->setScene(new SceneMap());
		return true;
	}
	if (m_pGM->isKeyPressed(Key::Num4))
	{
		m_pGM->setScene(new SceneSteering());
		return true;
	}
	if (m_pGM->isKeyPressed(Key::Escape))
	{
		return false;
	}

	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onUpdate();
	}

	return true;
}

bool ScenePlanning::onDraw()
{
	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onDraw();
	}

	return true;
}

bool ScenePlanning::onQuit()
{
	// AI Tools
	if (m_bUseAITools)
	{
		m_pAITools->onQuit();
	}

	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	delete m_pCellsScriptFactory;

	return true;
}

