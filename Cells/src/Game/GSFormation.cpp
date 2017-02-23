#include "stdafx.h"

#include "Game\GSFormation.h"
#include "Game\GSMenu.h"
#include "Game\GSGame.h"
#include "Game\GSMap.h"
#include "Game\GSSteering.h"
#include "Core\SceneManager.h"
#include "Core\ICore.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\ISprite.h"
#include "AI\Steering\Steering.h"
#include "AI\Steering\Behavior.h"


GSFormation::GSFormation()
{

}

GSFormation::~GSFormation()
{

}

void GSFormation::deleteEntities()
{
	for (int i = 0; i < m_iNbEntities; i++)
	{
		m_pGM->clearEntity(m_vEntities[i]);
	}
	m_vEntities.clear();
}

void GSFormation::createEntities()
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

void GSFormation::setBehavior()
{
	for (int i = 0; i < m_iNbEntities; i++)
	{
		std::string s = std::to_string(i);
		Steering* pSteering = m_pGM->getSteering(s);
		pSteering->init();
		pSteering->clearBehaviors();
		// Behavior
		switch (m_iSteeringMode)
		{
		case 0: pSteering->addBehavior(new FormationV(m_vEntities[i], m_pMouse, true, 10, i, m_iNbEntities, 60.0f, 100.0f, MathTools::degreetoradian(45.0f)), 1.0f);
			break;
		case 1: pSteering->addBehavior(new FormationV(m_vEntities[i], m_pMouse, false, 10, i, m_iNbEntities, 60.0f, 100.0f, 0.0f), 1.0f);
			break;
		case 2: pSteering->addBehavior(new FormationCircle(m_vEntities[i], m_pMouse, false, 10, i, m_iNbEntities, 60.0f, 100.0f, -90.0f, 90.0f, 60.0f), 1.0f);
			break;
		case 3: 
			pSteering->addBehavior(new FormationV(m_vEntities[i], m_pMouse, true, 10, i, m_iNbEntities, 60.0f, 100.0f, MathTools::degreetoradian(45.0f)), 1.0f);
			pSteering->addBehavior(new ObstacleAvoidance(m_vEntities[i], 12, 100, &m_vObstacles), 8.0f);
			break;
		case 4 : 
			if (i >= 23)
			{
				pSteering->addBehavior(new FormationV(m_vEntities[i], m_vEntities[1], false, 10, i - 23, m_iNbEntities - 23, 60.0f, 100.0f, MathTools::degreetoradian(0.0f)), 1.f);
			}
			else if (i >= 13)
			{
				pSteering->addBehavior(new FormationCircle(m_vEntities[i], m_vEntities[2], false, 10, i - 13, 10, 60.0f, 100.0f, 0.0f, 360.0f, 60.0f), 1.f);
			}
			else if (i >= 3)
			{
				pSteering->addBehavior(new FormationCircle(m_vEntities[i], m_vEntities[0], false, 10, i - 3, 10, 60.0f, 100.0f, 0.0f, 360.0f, 60.0f), 1.f);
			}
			else
			{
				pSteering->addBehavior(new FormationV(m_vEntities[i], m_pMouse, false, 10, i, 3, 200.0f, 100.0f, MathTools::degreetoradian(-45.0f)), 1.f);
			}
			break;
		case 5: 			
			pSteering->addBehavior(new FormationDynamic(m_vEntities[i], m_pMouse, false, 10, i, m_iNbEntities, 60.0f, 100.0f, -90.0f, 90.0f, 60.0f), 1.f);
			break;
		}
	}
}

bool GSFormation::onInit()
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

	// Obstacles
	Entity* pEntityObstacle = m_pGM->getEntity("o1");
	pEntityObstacle->setPosition(Vector2f(100, 600));
	Collider* pCollider = m_pGM->getCollider("Obstacle/Obstacle1.col");
	pEntityObstacle->addComponent(pCollider);
	m_pGM->addEntity(pEntityObstacle);
	m_vObstacles.push_back(pEntityObstacle);

	pEntityObstacle = m_pGM->getEntity("o2");
	pEntityObstacle->setPosition(Vector2f(600, 600));
	pCollider = m_pGM->getCollider("Obstacle/Obstacle2.col");
	pEntityObstacle->addComponent(pCollider);
	m_pGM->addEntity(pEntityObstacle);
	m_vObstacles.push_back(pEntityObstacle);

	pEntityObstacle = m_pGM->getEntity("o3");
	pEntityObstacle->setPosition(Vector2f(600, 100));
	pCollider = m_pGM->getCollider("Obstacle/Obstacle3.col");
	pEntityObstacle->addComponent(pCollider);
	m_pGM->addEntity(pEntityObstacle);
	m_vObstacles.push_back(pEntityObstacle);

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
	m_pTextSteeringMode->setString("Formation V");

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

bool GSFormation::onUpdate()
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

	// Steering mode
	if (m_pGM->isKeyPressed(Key::Numpad0))
	{
		m_iSteeringMode = 0;
		m_pTextSteeringMode->setString("Formation V");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad1))
	{
		m_iSteeringMode = 1;
		m_pTextSteeringMode->setString("Formation L");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad2))
	{
		m_iSteeringMode = 2;
		m_pTextSteeringMode->setString("Formation Circle");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad3))
	{
		m_iSteeringMode = 3;
		m_pTextSteeringMode->setString("Formation 2-Level");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad4))
	{
		m_iSteeringMode = 4;
		m_pTextSteeringMode->setString("Formation of formation");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad5))
	{
		m_iSteeringMode = 5;
		m_pTextSteeringMode->setString("Dynamic formation");
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

bool GSFormation::onDraw()
{
	return true;
}

bool GSFormation::onQuit()
{	
	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

