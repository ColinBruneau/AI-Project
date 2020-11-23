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

	// Sprite
	m_pSprite1 = m_pGM->getSprite("LocoRotux");
	m_pSprite1->setTexture(m_pGM->getTexture("image.png")); 
	//m_pSprite1->setTextureRect(0, 0, 16, 16);

	// SpriteRenderer
	m_pSpriteRenderer = m_pGM->getSpriteRenderer("LocoRotuxSR");
	m_pSpriteRenderer->setSprite(m_pSprite1);

	// Entity
	m_pEntity1 = m_pGM->getEntity("sprite 1");
	m_pEntity1->setName(string("sprite 1"));
	m_pEntity1->setPosition(Vector2f(800, 300));
	m_pEntity1->addComponent(m_pSpriteRenderer);

	m_pGM->addEntity(m_pEntity1);

	
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

