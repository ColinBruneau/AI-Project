#include "stdafx.h"

#include "Scene\SceneGame.h"
#include "Scene\SceneMenu.h"
#include "Core\SceneManager.h"

SceneGame::SceneGame()
{

}

SceneGame::~SceneGame()
{

}
	
bool SceneGame::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Set Script factory
	m_pCellsScriptFactory = new CellsScriptFactory;
	m_pGM->setScriptFactory(m_pCellsScriptFactory);
/*
	// Sprite
	m_pSprite1 = m_pGM->getSprite("loco");
	m_pSprite1->setTexture(m_pGM->getTexture("image.png"));
	m_pSprite1->setPosition(300, 150);

	// SpriteRenderer
	m_pSpriteRenderer = m_pGM->getSpriteRenderer("locoSpriteRenderer");
	m_pSpriteRenderer->setSprite(m_pSprite1);

	// Entity
	m_pEntity1 = m_pGM->getEntity("locoEntity");
	m_pEntity1->setName(string("sprite 1"));
	m_pEntity1->addComponent(m_pSpriteRenderer);

	m_pGM->addEntity(m_pEntity1);
	*/
	Entity* pEntity = m_pGM->getEntity("test");
	string n = "Peon/peon1.ent";
	Entity* pModel = m_pGM->getEntityByModel(n);
	if (pModel)
	{
		pEntity->cloneComponents(pModel);
	}
	else
	{
		pEntity->loadFromFileJSON(DATAAGENTPATH + n);
		m_pGM->addEntityByModel(n, pEntity);
	}
	pEntity->setPosition(Vector2f((float)200, (float)200));

	m_pGM->addEntity(pEntity);
	pEntity->selectEntities(FloatRect(0, 0, 300, 300));

	return true;
}

bool SceneGame::onUpdate()
{
	// Get direction from keyboard
	if (m_pGM->isKeyPressed(Key::Num1))
	{
		m_pGM->setScene(new SceneMenu());
		return true;
	}

	return true;
}

bool SceneGame::onDraw()
{
	return true;
}

bool SceneGame::onQuit()
{
	m_pGM->clearAllEntities();

	return true;
}

