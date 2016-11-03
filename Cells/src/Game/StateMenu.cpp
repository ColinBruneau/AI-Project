#include "stdafx.h"

#include "Game\StateMenu.h"
#include "Game\StateGame.h"
#include "Game\StateMap.h"
#include "Core\SceneManager.h"
#include "Core\GameManager.h"
#include "Core\DataManager.h"
#include "Core\EntityManager.h"
#include "Data\Entity.h"
#include "Graphics\SpriteRenderer.h"

StateMenu::StateMenu()
{

}

StateMenu::~StateMenu()
{

}
	
bool StateMenu::onInit()
{
	m_pGM = crea::GameManager::getSingleton();

	// Text
	crea::IColor* pRed = m_pGM->getColor("Red");
	pRed->setValues(255, 0, 0, 255);

	crea::IText* pText = m_pGM->getText("Menu Text");
	pText->setFont(m_pGM->getFont("arial.ttf"));
	pText->setColor(pRed);
	pText->setCharacterSize(20);
	pText->setString("fps");

	crea::TextRenderer* pTextRenderer = m_pGM->getTextRenderer("TextRenderer1");
	pTextRenderer->setText(pText);

	crea::Entity* pEntity1 = m_pGM->getEntity("text 1");
	pEntity1->addComponent(pTextRenderer);

	m_pGM->addEntity(pEntity1);

	return true;
}

bool StateMenu::onUpdate()
{
	// Get direction from keyboard
	if(m_pGM->isKeyPressed(crea::Key::Num2))
	{
		m_pGM->setState(new StateGame());
	}

	if (m_pGM->isKeyPressed(crea::Key::Num3))
	{
		m_pGM->setState(new StateMap());
		return true;
	}

	return true;
}

bool StateMenu::onDraw()
{
	return true;
}

bool StateMenu::onQuit()
{
	m_pGM->clearAllEntities();
	m_pGM->clearAllData();

	return true;
}

