#include "stdafx.h"

#include "Game\GSMenu.h"
#include "Game\GSGame.h"
#include "Game\GSMap.h"
#include "Game\GSFormation.h"
#include "Game\GSSteering.h"
#include "Game\GSBehaviorTree.h"
#include "Core\SceneManager.h"
#include "Core\GameManager.h"
#include "Core\DataManager.h"
#include "Core\EntityManager.h"
#include "Data\Entity.h"
#include "Graphics\SpriteRenderer.h"

GSMenu::GSMenu()
{

}

GSMenu::~GSMenu()
{

}
	
bool GSMenu::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Text
	crea::IColor* pRed = m_pGM->getColor("Red");
	pRed->setValues(255, 0, 0, 255);

	crea::IText* pText = m_pGM->getText("GSMenu Text");
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

bool GSMenu::onUpdate()
{
	// Get direction from keyboard
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
	if (m_pGM->isKeyPressed(Key::Num3))
	{
		m_pGM->setGameState(new GSSteering());
		return true;
	}
	if (m_pGM->isKeyPressed(Key::Num4))
	{
		m_pGM->setGameState(new GSFormation());
		return true;
	}
	if (m_pGM->isKeyPressed(Key::Num5))
	{
		m_pGM->setGameState(new GSBehaviorTree());
		return true;
	}

	return true;
}

bool GSMenu::onDraw()
{
	return true;
}

bool GSMenu::onQuit()
{
	m_pGM->clearAllEntities();
	m_pGM->clearAllData();

	return true;
}

