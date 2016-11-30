#include "stdafx.h"

#include "Game\StateGame.h"
#include "Game\StateMenu.h"
#include "Game\StateMap.h"
#include "Core\SceneManager.h"
#include "Core\ICore.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\ISprite.h"
#include "Core\TimeManager.h"


StateGame::StateGame()
{

}

StateGame::~StateGame()
{

}
	
bool StateGame::onInit()
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

	// Sprite
	m_pSprite1 = m_pGM->getSprite("image");
	m_pSprite1->setTexture(m_pGM->getTexture("image.png"));
	m_pSprite1->setPosition(300, 150);

	m_pSpriteRenderer = m_pGM->getSpriteRenderer("SpriteRenderer1");
	m_pSpriteRenderer->setSprite(m_pSprite1);

	m_pEntity1 = m_pGM->getEntity("sprite 1"); 
	m_pEntity1->addComponent(m_pSpriteRenderer);

	m_pGM->addEntity(m_pEntity1);

	// Entity 2
	m_pEntity2 = m_pGM->getEntity(string("animated sprite 1"));
	m_pEntity2->setPosition(Vector2f(300.f, 150.f));
	m_pGM->addEntity(m_pEntity2);

	// Animated Sprite
	m_pSprite2 = m_pGM->getSprite("Sprite2");	
	m_pSpriteRenderer2 = m_pGM->getSpriteRenderer("SpriteRenderer2");
	m_pSpriteRenderer2->setSprite(m_pSprite2);
	m_pEntity2->addComponent(m_pSpriteRenderer2);
	
	// Load Animator
	m_pAnimator = m_pGM->getAnimator("Animator1");
	m_pAnimator->setSprite(m_pSprite2);
	m_pEntity2->addComponent(m_pAnimator);

	// Load ActionTable
	m_pActionTable = m_pGM->getActionTable("Peon/Peon.act");

	// Collider
	m_pCollider = m_pGM->getCollider("Peon/Peon.col");
	CircleCollider* pCircleCollider = (CircleCollider*) m_pCollider->getCollider();
	pCircleCollider->getCenter() = Vector2f(0.f, 0.f);
	pCircleCollider->getRadius() = 16.f;
	m_pEntity2->addComponent(m_pCollider);

	// Character Controller
	m_pCharacterController = m_pGM->getCharacterController("Peon/Peon.cc");
	m_pCharacterController->setAnimator(m_pAnimator);
	m_pCharacterController->setActionTable(m_pActionTable);
	m_pCharacterController->setCollider(m_pCollider);
	m_pEntity2->addComponent(m_pCharacterController);

	// User controller
	m_pUserController = m_pGM->getUserController("Peon/Peon.uc");
	m_pUserController->setCharacterController(m_pCharacterController);
	m_pEntity2->addComponent(m_pUserController);


	return true;
}

bool StateGame::onUpdate()
{
	// Get direction from keyboard
	if (m_pGM->isKeyPressed(Key::Num1))
	{
		m_pGM->setState(new StateMenu());
		return true;
	}

	if (m_pGM->isKeyPressed(Key::Num3))
	{
		m_pGM->setState(new StateMap());
		return true;
	}

	// FPS
	Time frameTime = TimeManager::getSingleton()->getFrameTime();
	m_pTextFPS->setString("                              " + to_string((int)(1/frameTime.asSeconds())) + " fps");

	return true;
}

bool StateGame::onDraw()
{
	return true;
}

bool StateGame::onQuit()
{	
	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

