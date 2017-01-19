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

void GSSteering::deleteEntities()
{
	for (int i = 0; i < m_iNbEntities; i++)
	{
		m_pGM->clearEntity(m_vEntities[i]);
	}
	m_vEntities.clear();
}

void GSSteering::createEntities()
{
	ITexture* pTexture1 = m_pGM->getTexture("image.png");
	ITexture* pTexture2 = m_pGM->getTexture("image2.png");
	for (int i = 0; i < m_iNbEntities; i++)
	{
		std::string s = std::to_string(i);
		Entity* pEntityCell1 = m_pGM->getEntity(s);
		ISprite* pSprite1 = m_pGM->getSprite(s);
		pSprite1->setOrigin(32, 32);
		SpriteRenderer* pSP = m_pGM->getSpriteRenderer(s);
		pSP->setSprite(pSprite1);
		pEntityCell1->addComponent(pSP);
		Steering* pSteering = m_pGM->getSteering(s);
		pEntityCell1->addComponent(pSteering);
		m_pGM->addEntity(pEntityCell1);

		m_vEntities.push_back(pEntityCell1); // Keep pointers on entities

		// Position random
		int x = rand() % m_rWindowRect.getWidth();
		int y = rand() % m_rWindowRect.getHeight();
		pEntityCell1->setPosition(Vector2f((float)x, (float)y));

		// Behavior
		if (i % 2 == 0)
		{
			pSprite1->setTexture(pTexture1);
		}
		else
		{
			pSprite1->setTexture(pTexture2);
		}
	}
}

void GSSteering::setBehavior()
{
	for (int i = 0; i < m_iNbEntities; i++)
	{
		std::string s = std::to_string(i);
		Steering* pSteering = m_pGM->getSteering(s);
		pSteering->init();
		pSteering->clearBehaviors();
		// Behavior
		if (i % 2 == 0)
		{
			switch (m_iSteeringMode)
			{
			case 0: pSteering->addBehavior(new Seek(m_vEntities[i], m_pMouse), 1.0f);
				break;
			case 1: pSteering->addBehavior(new Pursuit(m_vEntities[i], m_vEntities[i + 1], 1.0f), 1.0f);
				break;
			case 2: pSteering->addBehavior(new Arrival(m_vEntities[i], m_pMouse, 200.0f), 1.0f);
				break;
			}

		}
		else
		{
			switch (m_iSteeringMode)
			{
			case 0: pSteering->addBehavior(new Flee(m_vEntities[i], m_pMouse), 1.0f);
				break;
			case 1: pSteering->addBehavior(new Evasion(m_vEntities[i], m_vEntities[i-1], 1.f), 1.0f);
				break;
			case 2: pSteering->addBehavior(new Arrival(m_vEntities[i], m_pMouse, 200.0f), 1.0f);
				break;
			}
		}
	}
}

bool GSSteering::onInit()
{
	m_pGM = GameManager::getSingleton();
	m_rWindowRect = m_pGM->getRenderer()->getWindowRect();

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
	pEntityFPS->setPosition(Vector2f(1100, 0));
	m_pGM->addEntity(pEntityFPS);

	// Steering mode
	m_pTextSteeringMode = m_pGM->getText("steering");
	m_pTextSteeringMode->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextSteeringMode->setColor(pRed);
	m_pTextSteeringMode->setCharacterSize(20);
	m_pTextSteeringMode->setString("steering mode");
	TextRenderer* pTextRendererSteering = m_pGM->getTextRenderer("TextRenderer steering");
	pTextRendererSteering->setText(m_pTextSteeringMode);
	Entity* pEntitySteering = m_pGM->getEntity("text steering mode");
	pEntitySteering->addComponent(pTextRendererSteering);
	pEntitySteering->setPosition(Vector2f(0, 0));
	m_pGM->addEntity(pEntitySteering);

	m_iSteeringMode = 0;
	m_pTextSteeringMode->setString("Seek/Flee");

	// Mouse Entity
	m_pMouse = m_pGM->getEntity("mouse");
	m_pMouse->setPosition(InputManager::getSingleton()->getMousePosition());

	// n entity
	m_iNbEntities = 2;
	m_bKeyPressedAdd = false;
	m_bKeyPressedSub = false;

	createEntities();
	setBehavior();
		
	return true;
}

bool GSSteering::onUpdate()
{
	// Mouse entity
	m_pMouse->setPosition(InputManager::getSingleton()->getMousePosition());

	// entities leaving the window
	for (int i = 0; i < m_iNbEntities; i++)
	{
		Entity* pEntity = m_vEntities[i];
		Vector2f vPos = pEntity->getPosition();
		if (vPos.getX() < 0.f)
		{
			vPos.setX(0.f);
			pEntity->setPosition(vPos);
		}
		else if (vPos.getX() > m_rWindowRect.getWidth())
		{
			vPos.setX((float)m_rWindowRect.getWidth());
			pEntity->setPosition(vPos);
		}
		if (vPos.getY() < 0.f)
		{
			vPos.setY(0.f);
			pEntity->setPosition(vPos);
		}
		else if (vPos.getY() > m_rWindowRect.getHeight())
		{
			vPos.setY((float)m_rWindowRect.getHeight());
			pEntity->setPosition(vPos);
		}
	}

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

	// Steering mode
	if (m_pGM->isKeyPressed(Key::Numpad0))
	{
		m_iSteeringMode = 0;
		m_pTextSteeringMode->setString("Seek/Flee");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad1))
	{
		m_iSteeringMode = 1;
		m_pTextSteeringMode->setString("Pursuit/Evasion");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad2))
	{
		m_iSteeringMode = 2;
		m_pTextSteeringMode->setString("Arrival");
		setBehavior();
	}

	// Entities
	if (m_pGM->isKeyPressed(Key::Add))
	{
		if (!m_bKeyPressedAdd && m_iNbEntities < 100)
		{
			deleteEntities();
			m_iNbEntities += 10;
			createEntities();
			setBehavior();
		}
		m_bKeyPressedAdd = true;
	}
	else
	{
		m_bKeyPressedAdd = false;
	}

	if (m_pGM->isKeyPressed(Key::Subtract))
	{
		if (!m_bKeyPressedSub && m_iNbEntities > 10)
		{
			deleteEntities();
			m_iNbEntities -= 10;
			createEntities();
			setBehavior();
		}
		m_bKeyPressedSub = true;
	}
	else
	{
		m_bKeyPressedSub = false;
	}

	// FPS
	Time frameTime = TimeManager::getSingleton()->getFrameTime();
	m_pTextFPS->setString(to_string((int)(1/frameTime.asSeconds())) + " fps");

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

