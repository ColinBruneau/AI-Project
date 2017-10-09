#include "stdafx.h"

#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"
#include "Scene\SceneMap.h"
#include "Scene\SceneFormation.h"
#include "Scene\SceneSteering.h"
#include "Scene\SceneBehaviorTree.h"
#include "Core\SceneManager.h"
#include "Core\ICore.h"
#include "Graphics\SpriteRenderer.h"
#include "Graphics\ISprite.h"
#include "Core\TimeManager.h"
#include "AI\StateMachine.h"
#include "AI\Pathfinding\MapSearchManager.h"
#include "Scene\Messages.h"


SceneGame::SceneGame()
{

}

SceneGame::~SceneGame()
{

}
	
bool SceneGame::onInit()
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

	// Set Map as pathfinding space
	MapSearchManager::getSingleton()->setMap(m_pMap);

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
	pEntityFPS->setPosition(Vector2f(1100, 0));

	m_pGM->addEntity(pEntityFPS);
	
	// Entity 1
	m_pAgent1 = m_pGM->getAgent("Peon/Peon1.chr");
	m_pFSMPeon1 = new FSMPeon(m_pAgent1);
	m_pAgent1->SetStateMachine(m_pFSMPeon1); // CB: can't we just call SetStateMachine in FSMPeon?

	
	// Entity 2
	//m_pAgent2 = m_pGM->getAgent("Peon/Peon2.chr");
	//m_pFSMPeon2 = new FSMPeon(m_pAgent2);
	//m_pAgent2->SetStateMachine(m_pFSMPeon2); // CB: can't we just call SetStateMachine in FSMPeon?


	// Commands
	ITexture* pCommandsTexture = m_pGM->getTexture("debug/Commands.png");
	ISprite* pCommandsSprite = m_pGM->getSprite("Commands");
	pCommandsSprite->setTexture(pCommandsTexture);

	SpriteRenderer* pSpriteRenderer = m_pGM->getSpriteRenderer("ResetRenderer");
	pSpriteRenderer->setSprite(pCommandsSprite);

	Entity* pEntityReset = m_pGM->getEntity("Sprite reset");
	pEntityReset->addComponent(pSpriteRenderer);
	pEntityReset->setPosition(Vector2f(1000, 500));

	m_pGM->addEntity(pEntityReset);

	// Diagnostics
	IColor* pBlue = m_pGM->getColor("Blue");
	pBlue->setValues(0, 0, 255, 255);

	m_pTextDiagnostics = m_pGM->getText("Diagnostics");
	m_pTextDiagnostics->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextDiagnostics->setColor(pBlue);
	m_pTextDiagnostics->setCharacterSize(14);
	m_pTextDiagnostics->setPosition(-100.f, -100.f);

	m_pPathSprite = crea::GameManager::getSingleton()->getSprite("debug/path");
	m_pPathSprite->setTexture(crea::GameManager::getSingleton()->getTexture("debug/path.png"));
	m_pPathSprite->setOrigin(64, 64);
	m_pPathSprite->setScale(ONEOVER128 * 32, ONEOVER128 * 32);

	return true;
}

bool isButton(int _i, Vector2f& _vMousePosition)
{
	int i = _i % 5;
	int j = _i / 5;
	FloatRect r(1000.f + i * 46, 500.f + j * 38, 46.f, 38.f);
	if (r.contains(_vMousePosition))
	{
		return true;
	}
	return false;
}

bool SceneGame::onUpdate()
{
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

	// FPS
	Time frameTime = TimeManager::getSingleton()->getFrameTime();
	m_pTextFPS->setString(to_string((int)(1/frameTime.asSeconds())) + " fps");

	// Selection
	if (m_pGM->isMouseButtonPressed(Button::MouseRight))
	{
		if (!m_bSelection) // just pressed
		{
			m_vStartSelection = m_pGM->getMousePosition();
		}
		m_bSelection = true;
	}
	else
	{
		if (m_bSelection) // just released
		{
			m_vEndSelection = m_pGM->getMousePosition();
			m_pGM->unselectEntities();
			m_pGM->selectEntities(m_vStartSelection, m_vEndSelection);
		}
		m_bSelection = false;
	}

	// Command
	if (m_pGM->isMouseButtonPressed(Button::MouseMiddle))
	{
		if (!m_bCommand) // just pressed
		{
			m_eCommandType = Command_Invalid;
			Vector2f vMousePosition = m_pGM->getMousePosition();
			FloatRect rect(1000, 500, 256, 256);
			if (rect.contains(vMousePosition))
			{
				if (isButton(0, vMousePosition))
				{
					m_eCommandType = Command_Reset;
				}
				else if (isButton(1, vMousePosition))
				{
					m_eCommandType = Command_Kill;
				}
				else if (isButton(2, vMousePosition))
				{
					m_eCommandType = Command_Stop;
				}
				else if (isButton(3, vMousePosition))
				{
					m_eCommandType = Command_Start;
				}
				else if (isButton(4, vMousePosition))
				{
					m_eCommandType = Command_Teleport;
				}
			}
		}
		m_bCommand = true;
	}
	else
	{
		if (m_bCommand) // just released
		{
			// Do the command
			ListEntity* pSelectedEntities = m_pGM->getSelectedEntities();
			for (ListEntity::iterator i = pSelectedEntities->begin(); i != pSelectedEntities->end(); ++i)
			{
				Entity* pEntity = (Entity*)*i;
				if (m_eCommandType == Command_Reset)
				{
					Agent* pAgent = pEntity->getComponent<Agent>();
					if (pAgent)
					{
						pAgent->GetStateMachine()->SendDelayedMsgToMe(0.f, MSG_Reset);
					}
				}
				else if (m_eCommandType == Command_Kill)
				{
					Agent* pAgent = pEntity->getComponent<Agent>();
					if (pAgent)
					{
						pAgent->GetStateMachine()->SendDelayedMsgToMe(0.f, MSG_Die);
					}
				}
				else if (m_eCommandType == Command_Stop)
				{
					Agent* pAgent = pEntity->getComponent<Agent>();
					if (pAgent)
					{
						pAgent->GetStateMachine()->SendDelayedMsgToMe(0.f, MSG_Stop);
					}
				}
				else if (m_eCommandType == Command_Start)
				{
					Agent* pAgent = pEntity->getComponent<Agent>();
					if (pAgent)
					{
						pAgent->GetStateMachine()->SendDelayedMsgToMe(0.f, MSG_Start);
					}
				}
				else if (m_eCommandType == Command_Teleport)
				{
					Agent* pAgent = pEntity->getComponent<Agent>();
					if (pAgent)
					{
						pAgent->GetStateMachine()->SendDelayedMsgToMe(0.f, MSG_Teleport);
					}
				}
			}

			m_eCommandType = Command_Invalid;
		}
		m_bCommand = false;
	}

	return true;
}

bool SceneGame::onDraw()
{
	// Diagnostics
	ListEntity* pSelectedEntities = m_pGM->getSelectedEntities();
	for (ListEntity::iterator i = pSelectedEntities->begin(); i != pSelectedEntities->end(); ++i)
	{
		Entity* pEntity = (Entity*)*i;
		Vector2f position = pEntity->getPosition();
		m_pTextDiagnostics->setPosition(position.getX(), position.getY()+10);
		string szDiagnostics; 
		szDiagnostics += pEntity->getName();
		Agent* pAgent = pEntity->getComponent<Agent>();
		if (pAgent)
		{
			// Stats
			szDiagnostics += "\nHea: ";
			szDiagnostics += to_string(pAgent->getHealth());
			szDiagnostics += " Str: ";
			szDiagnostics += to_string(pAgent->getStrength());
			szDiagnostics += " Int: ";
			szDiagnostics += to_string(pAgent->getIntelligence());
			szDiagnostics += " Dex: ";
			szDiagnostics += to_string(pAgent->getDexterity());

			// State
			StateMachine* pFSM = pAgent->GetStateMachine();
			if (pFSM)
			{
				FSMPeon* pFSMPeon = (FSMPeon*)pFSM;
				szDiagnostics += "\nFSM Peon: ";
				switch (pFSM->GetState())
				{
				case 0:szDiagnostics += "STATE_Spawn"; break;
				case 1:szDiagnostics += "STATE_Live"; break;
				case 2:szDiagnostics += "STATE_Die"; break;
				}
				FSMPeonLive* pFSMLive = pFSMPeon->getFSMPeonLive();
				if (pFSMLive)
				{
					szDiagnostics += "\nFSM Live: ";
					switch (pFSMLive->GetState())
					{
					case 0:szDiagnostics += "STATE_Idle"; break;
					case 1:szDiagnostics += "STATE_GoTo"; break;
					case 2:szDiagnostics += "STATE_GetResource"; break;
					case 3:szDiagnostics += "STATE_DropResource"; break;
					case 4:szDiagnostics += "STATE_Hit"; break;
					}
					FSMPeonGoTo* pFSMGoTo = pFSMLive->getFSMPeonGoTo();
					if (pFSMGoTo)
					{
						szDiagnostics += "\nFSM GoTo: ";
						switch (pFSMGoTo->GetState())
						{
						case 0:szDiagnostics += "STATE_SearchPath"; break;
						case 1:szDiagnostics += "STATE_FollowPath"; break;
						case 2:szDiagnostics += "STATE_SearchFailed"; break;
						case 3:szDiagnostics += "STATE_CompletedPath"; break;
						}

						// Draw path
						VectorVector2f* path = pFSMGoTo->getPath();
						for (short i = 0; i < (short)path->size(); i++)
						{
							Vector2f* v = path->operator[](i);
							m_pPathSprite->setPosition(v->getX(), v->getY());
							m_pPathSprite->draw();
						}
					}
				}
			}

			// Animation
			Animator* pAnimator = pEntity->getComponent<Animator>();
			if (pAnimator)
			{
				szDiagnostics += "\nAnim: ";
				szDiagnostics += pAnimator->getAnimation()->getName();
			}

			
		}
		m_pTextDiagnostics->setString(szDiagnostics);
		m_pTextDiagnostics->draw();
	}

	return true;
}

bool SceneGame::onQuit()
{	
	m_pGM->clearAllData();
	m_pGM->clearAllEntities();

	return true;
}

