#include "stdafx.h"

#include "Game\StateMap.h"
#include "Game\StateMenu.h"
#include "Game\StateGame.h"


StateMap::StateMap()
{

}

StateMap::~StateMap()
{

}
	
bool StateMap::onInit()
{
	m_pGM = crea::GameManager::getSingleton();

	// Load Map
	m_pEntity3 = m_pGM->getEntity("map1");
	m_pGM->addEntity(m_pEntity3);
	m_pMap = m_pGM->getMap("map1.json"); // CB: TO CHANGE: map id loaded after entity added to display map first (order in tree matters)
	m_pMapRenderer = m_pGM->getMapRenderer("MapRenderer1");
	m_pMapRenderer->setMap(m_pMap);
	m_pEntity3->addComponent(m_pMapRenderer);

	return true;
}

bool StateMap::onUpdate()
{
	if (m_pGM->isKeyPressed('1'))
	{
		m_pGM->setState(new StateMenu());
		return true;
	}

	if (m_pGM->isKeyPressed('2'))
	{
		m_pGM->setState(new StateGame());
		return true;
	}

	// Collision
	if (m_pGM->isKeyPressed('c'))
	{
		m_pMap->setDisplayCollision(true);
	}
	else
	{
		m_pMap->setDisplayCollision(false);
	}

	return true;
}

bool StateMap::onDraw()
{
	return true;
}

bool StateMap::onQuit()
{
	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

