#include "stdafx.h"

#include "Game\GSMap.h"
#include "Game\GSMenu.h"
#include "Game\GSGame.h"


GSMap::GSMap()
{

}

GSMap::~GSMap()
{

}
	
bool GSMap::onInit()
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

bool GSMap::onUpdate()
{
	if (m_pGM->isKeyPressed(Key::Num1))
	{
		m_pGM->setGameState(new GSMenu());
		return true;
	}

	if (m_pGM->isKeyPressed(Key::Num2))
	{
		m_pGM->setGameState(new GSGame());
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

bool GSMap::onDraw()
{
	return true;
}

bool GSMap::onQuit()
{
	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

