#include "stdafx.h"

#include "Scene\SceneBehaviorTree.h"
#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"
#include "Scene\SceneMap.h"
#include "Scene\SceneSteering.h"
#include "Scene\SceneFormation.h"
#include "Core\SceneManager.h"
#include "Core\Math.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\ISprite.h"
#include "AI\Steering\Steering.h"
#include "AI\Steering\Behavior.h"
#include "AI\BehaviorTree\BehaviorTree.h"
#include "AI\BehaviorTree\BTBehavior.h"


SceneBehaviorTree::SceneBehaviorTree()
{

}

SceneBehaviorTree::~SceneBehaviorTree()
{

}

void SceneBehaviorTree::deleteEntities()
{
	for (int i = 0; i < m_iNbEntities; i++)
	{
		m_pGM->clearEntity(m_vEntities[i]);
	}
	m_vEntities.clear();
}

void SceneBehaviorTree::createEntities()
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

void SceneBehaviorTree::setBehavior()
{
	for (int i = 0; i < m_iNbEntities; i++)
	{
		std::string s = std::to_string(i);
		Steering* pSteering = m_pGM->getSteering(s);
		pSteering->init();
		pSteering->clearBehaviors();

		BehaviorTree* pBT = m_vEntities[i]->getComponent<BehaviorTree>();
		if (pBT)
		{
			m_vEntities[i]->removeComponent(pBT);
		}

		// Behavior
		switch (m_iBTMode)
		{
		case 1: 
			{
				Seek* pSeek = new Seek(m_vEntities[i], m_pMouse);
				SeekTo* pSeekTo = new SeekTo(pSeek, 10.0f);
				Flee* pFlee = new Flee(m_vEntities[i], m_pMouse);
				FleeUntil* pFleeUntil = new FleeUntil(pFlee, 300.0f);
				Sequence* pSeq = new Sequence;
				pSeq->addChild(pSeekTo);
				pSeq->addChild(pFleeUntil);
				BehaviorTree* pBT = new BehaviorTree();
				pBT->setRootBehavior(pSeq);
				m_vEntities[i]->addComponent(pBT);
			}
			break;
		case 2:
			{
				Seek* pSeek = new Seek(m_vEntities[i], m_pMouse);
				SeekTo* pSeekTo = new SeekTo(pSeek, 10.0f);
				Flee* pFlee = new Flee(m_vEntities[i], m_pMouse);
				FleeUntil* pFleeUntil = new FleeUntil(pFlee, 300.0f);
				Wander* pWander = new Wander(m_vEntities[i], 100.f, 50.f, 10.0f);
				BTWander* pBTWander = new BTWander(pWander);
				Sequence* pSeq = new Sequence;
				pSeq->addChild(pSeekTo);
				pSeq->addChild(pFleeUntil);
				pSeq->addChild(pBTWander);
				BehaviorTree* pBT = new BehaviorTree();
				pBT->setRootBehavior(pSeq);
				m_vEntities[i]->addComponent(pBT);
			}
			break;
		case 3:
		{
			Seek* pSeek = new Seek(m_vEntities[i], m_pMouse);
			SeekTo* pSeekTo = new SeekTo(pSeek, 10.0f);
			IsAwayFromTarget* pIsAwayFromTarget = new IsAwayFromTarget(m_pMouse, m_vObstacles[0], 64.f);
			Flee* pFlee = new Flee(m_vEntities[i], m_pMouse);
			FleeUntil* pFleeUntil = new FleeUntil(pFlee, 300.0f);
			Wander* pWander = new Wander(m_vEntities[i], 100.f, 50.f, 10.0f);
			BTWander* pBTWander = new BTWander(pWander);
			Sequence* pSeq = new Sequence;
			pIsAwayFromTarget->addChild(pSeq);
			pSeq->addChild(pSeekTo);
			pSeq->addChild(pFleeUntil);
			//pSeq->addChild(pBTWander);
			BehaviorTree* pBT = new BehaviorTree();
			pBT->setRootBehavior(pIsAwayFromTarget);
			m_vEntities[i]->addComponent(pBT);
		}
		break;
		case 4:
		{
			Seek* pSeek = new Seek(m_vEntities[i], m_pMouse);
			SeekTo* pSeekTo = new SeekTo(pSeek, 10.0f);
			IsAwayFromTarget* pIsAwayFromTarget = new IsAwayFromTarget(m_pMouse, m_vObstacles[0], 64.f);
			Flee* pFlee = new Flee(m_vEntities[i], m_pMouse);
			FleeUntil* pFleeUntil = new FleeUntil(pFlee, 300.0f);
			Wander* pWander = new Wander(m_vEntities[i], 100.f, 50.f, 10.0f);
			BTWander* pBTWander = new BTWander(pWander);
			Sequence* pSeq = new Sequence;
			Selector* pSel = new Selector;
			pIsAwayFromTarget->addChild(pSeq);
			pSeq->addChild(pSeekTo);
			pSeq->addChild(pFleeUntil);
			pSel->addChild(pIsAwayFromTarget);
			pSel->addChild(pBTWander);
			BehaviorTree* pBT = new BehaviorTree();
			pBT->setRootBehavior(pSel);
			m_vEntities[i]->addComponent(pBT);
		}
		break;
		case 5:
		{
			Seek* pSeek = new Seek(m_vEntities[i], m_pMouse);
			SeekTo* pSeekTo = new SeekTo(pSeek, 10.0f);
			Flee* pFlee = new Flee(m_vEntities[i], m_pMouse);
			FleeUntil* pFleeUntil = new FleeUntil(pFlee, 300.0f);
			Wander* pWander = new Wander(m_vEntities[i], 100.f, 50.f, 10.0f);
			BTWander* pBTWander = new BTWander(pWander);
			Sequence* pSeq = new Sequence;
			pSeq->addChild(pSeekTo);
			pSeq->addChild(pFleeUntil);
			Repeat* pRepeat = new Repeat(pSeq);
			pRepeat->setCount(3);
			Sequence* pSeqTop = new Sequence;
			pSeqTop->addChild(pRepeat);
			pSeqTop->addChild(pBTWander);
			BehaviorTree* pBT = new BehaviorTree();
			pBT->setRootBehavior(pSeqTop);
			m_vEntities[i]->addComponent(pBT);
		}
		break;
		case 6:
		{
			Seek* pSeek = new Seek(m_vEntities[i], m_pMouse);
			SeekTo* pSeekTo = new SeekTo(pSeek, 10.0f);
			Wander* pWander = new Wander(m_vEntities[i], 100.f, 50.f, 10.0f);
			BTWander* pBTWander = new BTWander(pWander);
			Timer* pTimer = new Timer(pBTWander);
			pTimer->setTimeLimit(3.f);
			Sequence* pSeq = new Sequence;
			pSeq->addChild(pTimer);
			pSeq->addChild(pSeekTo);
			BehaviorTree* pBT = new BehaviorTree();
			pBT->setRootBehavior(pSeq);
			m_vEntities[i]->addComponent(pBT);
		}
		break;
		case 7:
		{
			Wander* pWander = new Wander(m_vEntities[i], 100.f, 50.f, 10.0f);
			BTWander* pBTWander = new BTWander(pWander);
			EntityNameIs* pEntityNameIs = new EntityNameIs(m_vEntities[i], "0");
			pEntityNameIs->addChild(pBTWander);
			BehaviorTree* pBT = new BehaviorTree();
			pBT->setRootBehavior(pEntityNameIs);
			m_vEntities[i]->addComponent(pBT);
		}
		break;
		}
	}
}

bool SceneBehaviorTree::onInit()
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
	m_pTextBTMode = m_pGM->getText("steering");
	m_pTextBTMode->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextBTMode->setColor(pRed);
	m_pTextBTMode->setCharacterSize(20);
	m_pTextBTMode->setString("steering mode");
	TextRenderer* pTextRendererSteering = m_pGM->getTextRenderer("TextRenderer steering");
	pTextRendererSteering->setText(m_pTextBTMode);
	Entity* pEntitySteering = m_pGM->getEntity("text steering mode");
	pEntitySteering->addComponent(pTextRendererSteering);
	pEntitySteering->setPosition(Vector2f(0, 0));
	m_pGM->addEntity(pEntitySteering);

	m_iBTMode = 1;
	m_pTextBTMode->setString("Sequence: SeekTo / FleeUntil");

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

bool SceneBehaviorTree::onUpdate()
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

	// Steering mode
	if (m_pGM->isKeyPressed(Key::Numpad1))
	{
		m_iBTMode = 1;
		m_pTextBTMode->setString("Sequence: SeekTo / FleeUntil");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad2))
	{
		m_iBTMode = 2;
		m_pTextBTMode->setString("Sequence: SeekTo / FleeUntil / Wander");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad3))
	{
		m_iBTMode = 3;
		m_pTextBTMode->setString("Sequence: IsAwayFromTarget / SeekTo / FleeUntil / Wander");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad4))
	{
		m_iBTMode = 4;
		m_pTextBTMode->setString("Selector: IsAwayFromTarget / Sequence / SeekTo / FleeUntil OR Wander");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad5))
	{
		m_iBTMode = 5;
		m_pTextBTMode->setString("Repeat: 3 Sequence / SeekTo / FleeUntil THEN Wander");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad6))
	{
		m_iBTMode = 6;
		m_pTextBTMode->setString("Timer 3s on Wander THEN SeekTo");
		setBehavior();
	}
	if (m_pGM->isKeyPressed(Key::Numpad7))
	{
		m_iBTMode = 7;
		m_pTextBTMode->setString("Wander if EntityNameIs 0");
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

bool SceneBehaviorTree::onDraw()
{
	return true;
}

bool SceneBehaviorTree::onQuit()
{	
	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

