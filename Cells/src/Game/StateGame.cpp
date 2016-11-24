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
	m_pGM = crea::GameManager::getSingleton();
	// Load Map
	crea::Entity* m_pEntity3;
	crea::Map* m_pMap;
	crea::MapRenderer* m_pMapRenderer;
	m_pEntity3 = m_pGM->getEntity("map1");
	m_pGM->addEntity(m_pEntity3);
	m_pMap = m_pGM->getMap("map1.json"); // CB: TO CHANGE: map id loaded after entity added to display map first (order in tree matters)
	m_pMapRenderer = m_pGM->getMapRenderer("MapRenderer1");
	m_pMapRenderer->setMap(m_pMap);
	m_pEntity3->addComponent(m_pMapRenderer);

	// Text
	crea::IColor* pRed = m_pGM->getColor("Red");
	pRed->setValues(255, 0, 0, 255);

	m_pTextFPS = m_pGM->getText("fps");
	m_pTextFPS->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextFPS->setColor(pRed);
	m_pTextFPS->setCharacterSize(20);
	m_pTextFPS->setString("fps");

	crea::TextRenderer* pTextRenderer = m_pGM->getTextRenderer("TextRenderer1");
	pTextRenderer->setText(m_pTextFPS);

	crea::Entity* pEntityFPS = m_pGM->getEntity("text 1");
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

	// Animated Sprite
	m_pSprite2 = m_pGM->getSprite("Sprite2");
	
	m_pSpriteRenderer2 = m_pGM->getSpriteRenderer("SpriteRenderer2");
	m_pSpriteRenderer2->setSprite(m_pSprite2);

	m_pAnimator = m_pGM->getAnimator("Animator1");
	m_pAnimator->setSprite(m_pSprite2);

	m_pEntity2 = m_pGM->getEntity(string("animated sprite 1"));
	m_pEntity2->addComponent(m_pSpriteRenderer2);
	m_pEntity2->addComponent(m_pAnimator);
	m_pEntity2->setPosition(crea::Vector2f(150.f, 150.f));

	speed = 80.f;
	noKeyWasPressed = true;

	m_pGM->addEntity(m_pEntity2);

	// Load ActionTable
	m_pActionTable = m_pGM->getActionTable("Peon/Peon.act");
	currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(kADir_Down, kACond_Default, kAct_Default, nullptr));
	m_CurrentCondition = kACond_Default;
	m_bAlive = true;
	m_bMoving = true;

	return true;
}

bool StateGame::onUpdate()
{
	// Get direction from keyboard
	if (m_pGM->isKeyPressed(crea::Key::Num1))
	{
		m_pGM->setState(new StateMenu());
		return true;
	}

	if (m_pGM->isKeyPressed(crea::Key::Num3))
	{
		m_pGM->setState(new StateMap());
		return true;
	}

	if (m_pGM->isKeyPressed(crea::Key::D))
	{
		m_CurrentCondition = kACond_Default;
		currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Idle));
		m_bAlive = true;
		m_bMoving = true;
	}

	if (m_pGM->isKeyPressed(crea::Key::G))
	{
		m_CurrentCondition = kACond_Gold;
		currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Idle));
		m_bAlive = true;
		m_bMoving = true;
	}

	if (m_pGM->isKeyPressed(crea::Key::L))
	{
		m_CurrentCondition = kACond_Lumber;
		currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Idle));
		m_bAlive = true;
		m_bMoving = true;
	}

	if (m_pGM->isKeyPressed(crea::Key::C))
	{
		m_CurrentCondition = kACond_Default;
		currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Chop));
		m_bAlive = true;
		m_bMoving = false;
		m_pAnimator->play(*currentAnimation);
	}

	if (m_pGM->isKeyPressed(crea::Key::K))
	{
		m_CurrentCondition = kACond_Default;
		currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Die));
		m_bAlive = false;
		m_bMoving = false;
		m_pAnimator->setLooped(false);
		m_pAnimator->play(*currentAnimation);
	}

	// FPS
	crea::Time frameTime = crea::TimeManager::getSingleton()->getFrameTime();
	m_pTextFPS->setString("                              " + to_string((int)(1/frameTime.asSeconds())) + " fps");

	if (m_bAlive)
	{
		// if a key was pressed set the correct animation and move correctly
		crea::Vector2f movement(0.f, 0.f);
		if (m_pGM->isKeyPressed(crea::Key::Up))
		{
			m_CurrentDirection = kADir_Up;
			currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Walk));
			movement.addY(-speed);
			noKeyWasPressed = false;
		}
		if (m_pGM->isKeyPressed(crea::Key::Down))
		{
			m_CurrentDirection = kADir_Down;
			currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Walk));
			movement.addY(+speed);
			noKeyWasPressed = false;
		}
		if (m_pGM->isKeyPressed(crea::Key::Left))
		{
			m_CurrentDirection = kADir_Left;
			currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Walk));
			movement.addX(-speed);
			noKeyWasPressed = false;
		}
		if (m_pGM->isKeyPressed(crea::Key::Right))
		{
			m_CurrentDirection = kADir_Right;
			currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Walk));
			movement.addX(speed);
			noKeyWasPressed = false;
		}

		// Diagonals
		if (m_pGM->isKeyPressed(crea::Key::Up) && m_pGM->isKeyPressed(crea::Key::Right))
		{
			m_CurrentDirection = kADir_UpRight;
			currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Walk));
		}
		if (m_pGM->isKeyPressed(crea::Key::Up) && m_pGM->isKeyPressed(crea::Key::Left))
		{
			m_CurrentDirection = kADir_UpLeft;
			currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Walk));
		}
		if (m_pGM->isKeyPressed(crea::Key::Down) && m_pGM->isKeyPressed(crea::Key::Right))
		{
			m_CurrentDirection = kADir_DownRight;
			currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Walk));
		}
		if (m_pGM->isKeyPressed(crea::Key::Down) && m_pGM->isKeyPressed(crea::Key::Left))
		{
			m_CurrentDirection = kADir_DownLeft;
			currentAnimation = m_pGM->getAnimation(*m_pActionTable->getAnimation(m_CurrentDirection, m_CurrentCondition, kAct_Walk));
		}

		m_pAnimator->play(*currentAnimation);
		if (m_bMoving)
		{
			m_pEntity2->move(movement * (float)frameTime.asSeconds());

			// if no key was pressed stop the animation
			if (noKeyWasPressed)
			{
				m_pAnimator->stop();
			}
		}

		noKeyWasPressed = true;
	}


	// update AnimatedSprite
	m_pAnimator->update();

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

