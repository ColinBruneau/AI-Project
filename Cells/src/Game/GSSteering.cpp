#include "stdafx.h"

#include "Game\GSSteering.h"
#include "Game\GSMenu.h"
#include "Game\GSGame.h"
#include "Game\GSMap.h"
#include "Core\SceneManager.h"
#include "Core\ICore.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\ISprite.h"
#include "AI\Steering\Steering.h"
#include "AI\Steering\Behavior.h"


GSSteering::GSSteering()
{

}

GSSteering::~GSSteering()
{

}
	
bool GSSteering::onInit()
{
	m_pGM = GameManager::getSingleton();

	// Text
	IColor* pRed = m_pGM->getColor("Red");
	pRed->setValues(255, 0,  0, 255);

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

	// 1 entity
	Entity* pEntityCell1 = m_pGM->getEntity("cell 1");

	ITexture* pTexture1 = m_pGM->getTexture("image.png");

	ISprite* pSprite1 = m_pGM->getSprite("sprite1");
	pSprite1->setTexture(pTexture1);
	pSprite1->setOrigin(32, 32);

	SpriteRenderer* pSP = m_pGM->getSpriteRenderer("sp1");
	pSP->setSprite(pSprite1);
	pEntityCell1->addComponent(pSP);

	Steering* pSteering = m_pGM->getSteering("Steering1");
	pEntityCell1->addComponent(pSteering);

	// Mouse Entity
	m_pMouse = m_pGM->getEntity("mouse");
	m_pMouse->setPosition(InputManager::getSingleton()->getMousePosition());

	pSteering->addBehavior(new Seek(pEntityCell1, m_pMouse), 1.0f);

	m_pGM->addEntity(pEntityCell1);
		
	return true;
}

bool GSSteering::onUpdate()
{
	m_pMouse->setPosition(InputManager::getSingleton()->getMousePosition());

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

bool GSSteering::onDraw()
{
	return true;
}

bool GSSteering::onQuit()
{	
	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

