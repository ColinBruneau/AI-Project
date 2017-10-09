#include "stdafx.h"

#include "Scene\SceneMap.h"
#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"
#include "Scene\SceneFormation.h"
#include "Scene\SceneSteering.h"
#include "Scene\SceneBehaviorTree.h"


SceneMap::SceneMap()
{

}

SceneMap::~SceneMap()
{

}
	
bool SceneMap::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Load Map
	m_pEntity3 = m_pGM->getEntity("map1");
	m_pGM->addEntity(m_pEntity3);
	m_pMap = m_pGM->getMap("map1.json"); // CB: TO CHANGE: map id loaded after entity added to display map first (order in tree matters)
	m_pMapRenderer = m_pGM->getMapRenderer("MapRenderer1");
	m_pMapRenderer->setMap(m_pMap);
	m_pEntity3->addComponent(m_pMapRenderer);

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

	return true;
}

bool SceneMap::onDraw()
{
	return true;
}

bool SceneMap::onQuit()
{
	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

