#include "stdafx.h"

#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"
#include "Scene\SceneMap.h"
#include "Scene\SceneFormation.h"
#include "Scene\SceneSteering.h"
#include "Scene\SceneBehaviorTree.h"
#include "Core\SceneManager.h"
#include "Core\GameManager.h"
#include "Core\DataManager.h"
#include "Core\EntityManager.h"
#include "Data\Entity.h"
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

	// Text
	crea::IColor* pRed = m_pGM->getColor("Red");
	pRed->setValues(255, 0, 0, 255);

	crea::IText* pText = m_pGM->getText("SceneMenu Text");
	pText->setFont(m_pGM->getFont("arial.ttf"));
	pText->setColor(pRed);
	pText->setCharacterSize(20);
	pText->setString("1) Menu 2) Game 3) Steering 4) Formation");

	crea::TextRenderer* pTextRenderer = m_pGM->getTextRenderer("TextRenderer1");
	pTextRenderer->setText(pText);

	crea::Entity* pEntity1 = m_pGM->getEntity("text 1");
	pEntity1->addComponent(pTextRenderer);

	m_pGM->addEntity(pEntity1);

	return true;
}

bool SceneMenu::onUpdate()
{
	// Get direction from keyboard
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

	return true;
}

bool SceneMenu::onDraw()
{
	return true;
}

bool SceneMenu::onQuit()
{
	m_pGM->clearAllEntities();
	m_pGM->clearAllData();

	return true;
}

