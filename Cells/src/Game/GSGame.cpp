#include "stdafx.h"

#include "Game\GSGame.h"
#include "Game\GSMenu.h"
#include "Game\GSMap.h"
#include "Core\SceneManager.h"
#include "Core\ICore.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\ISprite.h"
#include "Core\TimeManager.h"
#include "AI\StateMachine.h"
#include "AI\Pathfinding\MapSearchManager.h"


GSGame::GSGame()
{

}

GSGame::~GSGame()
{

}
	
bool GSGame::onInit()
{
	m_pGM = GameManager::getSingleton();

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

	// Text
	IColor* pRed = m_pGM->getColor("Red");
	pRed->setValues(255, 0, 0, 255);

	m_pTextFPS = m_pGM->getText("fps");
	m_pTextFPS->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextFPS->setColor(pRed);
	m_pTextFPS->setCharacterSize(20);
	m_pTextFPS->setString("fps");

	TextRenderer* pTextRenderer = m_pGM->getTextRenderer("TextRenderer1");
	pTextRenderer->setText(m_pTextFPS);

	Entity* pEntityFPS = m_pGM->getEntity("text 1");
	pEntityFPS->addComponent(pTextRenderer);

	m_pGM->addEntity(pEntityFPS);
	
	// Entity 1
	m_pAgent1 = m_pGM->getAgent("Peon/Peon1.chr");
	m_pFSMPeon1 = new FSMPeon(m_pAgent1);
	m_pAgent1->SetStateMachine(m_pFSMPeon1); // CB: can't we just call SetStateMachine in FSMPeon?

	// Entity 2
	//m_pAgent2 = m_pGM->getAgent("Peon/Peon2.chr");
	//m_pFSMPeon2 = new FSMPeon(m_pAgent2);
	//m_pAgent2->SetStateMachine(m_pFSMPeon2); // CB: can't we just call SetStateMachine in FSMPeon?

	return true;
}

bool GSGame::onUpdate()
{
	// Get direction from keyboard
	if (m_pGM->isKeyPressed(Key::Num1))
	{
		m_pGM->setGameState(new GSMenu());
		return true;
	}

	if (m_pGM->isKeyPressed(Key::Num3))
	{
		m_pGM->setGameState(new GSMap());
		return true;
	}

	// FPS
	Time frameTime = TimeManager::getSingleton()->getFrameTime();
	m_pTextFPS->setString("                              " + to_string((int)(1/frameTime.asSeconds())) + " fps");

	return true;
}

bool GSGame::onDraw()
{
	return true;
}

bool GSGame::onQuit()
{	
	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

