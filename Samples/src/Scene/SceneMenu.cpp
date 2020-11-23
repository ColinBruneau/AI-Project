#include "stdafx.h"

#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"
#include "Core\SceneManager.h"
#include "Core\GameManager.h"
#include "Data\DataManager.h"
#include "Core\EntityManager.h"
#include "Core\Entity.h"
#include "Graphics\SpriteRenderer.h"

SceneMenu::SceneMenu()
{

}

SceneMenu::~SceneMenu()
{

}
	
bool SceneMenu::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Color
	Color* pRed = m_pGM->getColor("Red");
	pRed->setValues(255, 0, 0, 255);

	// Text
	Text* m_pText = m_pGM->getText("text 1");
	m_pText->setFont(m_pGM->getFont("arial.ttf"));
	m_pText->setColor(pRed);
	m_pText->setCharacterSize(20);
	m_pText->setString("MENU. Press 1 to display Menu, 2 to display Game...");

	// TextRenderer
	m_pTextRenderer = m_pGM->getTextRenderer("FontTR");
	m_pTextRenderer->setText(m_pText);

	// Entity
	m_pEntity1 = m_pGM->getEntity("text 1 Entity");
	m_pEntity1->setName(string("text 1"));
	m_pEntity1->addComponent(m_pTextRenderer);

	m_pGM->addEntity(m_pEntity1);
	
	return true;
}

bool SceneMenu::onUpdate()
{
	// Get direction from keyboard
	if (m_pGM->isKeyPressed(Key::Num2))
	{
		m_pGM->setScene(new SceneGame());
		return true;
	}

	return true;
}

bool SceneMenu::onDraw()
{
	return true;
}

bool SceneMenu::onQuit()
{
	m_pGM->clearAllEntities();

	return true;
}

