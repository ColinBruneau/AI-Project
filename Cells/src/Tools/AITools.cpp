#include "stdafx.h"

#include "Tools\AITools.h"
#include "Scene\SceneMenu.h"
#include "Scene\SceneMap.h"
#include "Core\SceneManager.h"
#include "Scripts\Messages.h"
#include <string>

AITools::AITools()
{

}

AITools::~AITools()
{

}

bool AITools::onInit()
{
	m_pGM = GameManager::getSingleton();

	Color* pRed = m_pGM->getColor("Red");
	pRed->setValues(255, 0, 0, 255);
	Color* pBlue = m_pGM->getColor("Blue");
	pBlue->setValues(0, 0, 255, 255);
	Color* pBlack = m_pGM->getColor("Black");
	pBlack->setValues(0, 0, 0, 255);
	Color* pTransparent = m_pGM->getColor("Transparent");
	pTransparent->setValues(0, 0, 0, 0);
	Color* pRedTransparent = m_pGM->getColor("RedTransparent");
	pRedTransparent->setValues(255, 0, 0, 125);
	Color* pGreenTransparent = m_pGM->getColor("GreenTransparent");
	pGreenTransparent->setValues(0, 255, 0, 255);
	Color* pBlueTransparent = m_pGM->getColor("BlueTransparent");
	pBlueTransparent->setValues(0, 0, 255, 125);

	// Selection
	m_bSelection = false;
	m_pSelectionShape = (RectangleShape*)m_pGM->getShape("Rectangle", "SelectionShape");
	m_pSelectionShape->setOutlineColor(pBlue);
	m_pSelectionShape->setColor(pTransparent);
	m_pSelectionShape->setOutlineThickness(1.f);

	// Commands
	Texture* pCommandsTexture = m_pGM->getTexture("debug/Commands.png");
	m_pCommandsSprite = m_pGM->getSprite("Commands");
	m_pCommandsSprite->setTexture(pCommandsTexture);

	m_rCommandWindow = FloatRect(896, 640, 256, 256);
	m_pCommandsSprite->setPosition(m_rCommandWindow.m_fX, m_rCommandWindow.m_fY);

	// Diagnostics
	m_pTextFPS = m_pGM->getText("fps");
	m_pTextFPS->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextFPS->setColor(pRed);
	m_pTextFPS->setCharacterSize(14);
	m_pTextFPS->setString("fps:");
	m_pTextFPS->setPosition(900, 0);

	m_pTextCommand = m_pGM->getText("Command");
	m_pTextCommand->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextCommand->setColor(pRed);
	m_pTextCommand->setCharacterSize(14);
	m_pTextCommand->setString("Last command:");
	m_pTextCommand->setPosition(900, 20);

	m_pTextDiagnostics = m_pGM->getText("Diagnostics");
	m_pTextDiagnostics->setFont(m_pGM->getFont("arial.ttf"));
	m_pTextDiagnostics->setColor(pBlue);
	m_pTextDiagnostics->setCharacterSize(14);
	m_pTextDiagnostics->setPosition(-100.f, -100.f);

	m_fCommandDisplayTime = 1.0f;

	// Grid
	m_pMap = m_pGM->getMapRenderer("MapRenderer1")->getMap();
	m_pMap->getSize(m_nWidth, m_nHeight);
	m_pMap->getTileSize(m_nTileWidth, m_nTileHeight);
	m_pMap->getTileIndexLimits(m_iMin, m_iMax, m_jMin, m_jMax);
	m_pNodeShape = (RectangleShape*)m_pGM->getShape("Rectangle", "NodeShape");
	m_pNodeShape->setOutlineColor(pBlack);
	m_pNodeShape->setColor(pTransparent);
	m_pNodeShape->setOutlineThickness(0.5f);
	m_pNodeShape->setSize(m_nTileWidth, m_nTileHeight);
	
	m_pLineShape = (LineShape*)m_pGM->getShape("Line", "m_pLineShape");
	m_pLineShape->setColor(pBlack);

	// CharacterController
	//m_pCharacterController = (CharacterController*) m_pGM->getScript("CharacterController");
	m_pCharacterController = nullptr;

	m_pathToHQ.push_back(Vector2f(645.f, 125.f));
	m_pathToHQ.push_back(Vector2f(513.f, 97.f));
	m_pathToHQ.push_back(Vector2f(383.f, 97.f));
	m_pathToHQ.push_back(Vector2f(185.f, 130.f));

	m_pathToMine.push_back(Vector2f(185.f, 130.f));
	m_pathToMine.push_back(Vector2f(352.f, 191.f));
	m_pathToMine.push_back(Vector2f(608.f, 191.f));
	m_pathToMine.push_back(Vector2f(645.f, 125.f));

	// Collisions
	m_pBoxColliderShape = (RectangleShape*)m_pGM->getShape("Rectangle", "BoxColliderShape");
	m_pBoxColliderShape->setOutlineColor(pRed);
	m_pBoxColliderShape->setColor(pTransparent);
	m_pBoxColliderShape->setOutlineThickness(1.0f);
	m_pCircleColliderShape = (CircleShape*)m_pGM->getShape("Circle", "CircleColliderShape");
	m_pCircleColliderShape->setOutlineColor(pRed);
	m_pCircleColliderShape->setColor(pTransparent);
	m_pCircleColliderShape->setOutlineThickness(1.0f);
	m_pCollisionNodeShape = (RectangleShape*)m_pGM->getShape("Rectangle", "CollisionNodeShape");
	m_pCollisionNodeShape->setColor(pRedTransparent);
	m_pCollisionNodeShape->setSize(m_nTileWidth, m_nTileHeight);

	// Cluster
	m_pClusterShape = (RectangleShape*)m_pGM->getShape("Rectangle", "ClusterShape");
	m_pClusterShape->setOutlineColor(pBlue);
	m_pClusterShape->setColor(pTransparent);
	m_pClusterShape->setOutlineThickness(2.0f);
	m_pMap->getClusterSize(m_nClusterWidth, m_nClusterHeight);
	m_pClusterShape->setSize(m_nClusterWidth, m_nClusterHeight);
	m_pMap->getClusterIndexLimits(m_iClusterMin, m_iClusterMax, m_jClusterMin, m_jClusterMax);

	m_pEntranceShape = (RectangleShape*)m_pGM->getShape("Rectangle", "EntranceShape");
	m_pEntranceShape->setOutlineColor(pBlue);
	m_pEntranceShape->setColor(pBlueTransparent);
	m_pEntranceShape->setSize(m_nTileWidth, m_nTileHeight);

	m_pTransitionShape = (ArrowShape*)m_pGM->getShape("Arrow", "TransitionShape");
	m_pTransitionShape->setOutlineColor(pGreenTransparent);
	m_pTransitionShape->setColor(pGreenTransparent);
	m_pTransitionShape->setSize(m_nTileWidth, m_nTileHeight*0.5f);

	m_pEdgeShape = (ArrowShape*)m_pGM->getShape("Arrow", "EdgeShape");
	m_pEdgeShape->setOutlineColor(pRed);
	m_pEdgeShape->setColor(pRedTransparent);
	m_pEdgeShape->setSize(m_nTileWidth, m_nTileHeight*0.5f);

	//Steering
	m_pTarget = (LineShape*)m_pGM->getShape("Line", "Target");
	m_pTarget->setColor(pGreenTransparent);
	m_pSteeringLine = (LineShape*)m_pGM->getShape("Line", "Steering");
	m_pSteeringLine->setColor(pBlue);
	m_pForceLine = (LineShape*)m_pGM->getShape("Line", "Force");
	m_pForceLine->setColor(pBlack);
	m_pVelocityLine = (LineShape*)m_pGM->getShape("Line", "Velocity");
	m_pVelocityLine->setColor(pRed);

	return true;
}

bool AITools::isButton(int _i, Vector2f& _vMousePosition)
{
	int i = _i % 5;
	int j = _i / 5;
	FloatRect r(m_rCommandWindow.m_fX + i * 46, m_rCommandWindow.m_fY + j * 38, 46.f, 38.f);
	if (r.contains(_vMousePosition))
	{
		return true;
	}
	return false;
}

bool AITools::onUpdate()
{
	// FPS
	Time frameTime = TimeManager::getSingleton()->getFrameTime();
	m_pTextFPS->setString(to_string((int)(1 / frameTime.asSeconds())) + " fps");

	// Selection
	if (m_pGM->isMouseButtonPressed(Button::MouseLeft))
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
	if (m_pGM->isMouseButtonPressed(Button::MouseRight))
	{
		if (!m_bCommand) // just pressed
		{
			m_eCommandType = Command_Invalid;
			Vector2f vMousePosition = m_pGM->getMousePosition();
			if (m_rCommandWindow.contains(vMousePosition))
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
					m_eCommandType = Command_GoToHQ;
				}
				else if (isButton(4, vMousePosition))
				{
					m_eCommandType = Command_GoTo;
				}
				else if (isButton(5, vMousePosition))
				{
					m_eCommandType = Command_Build;
				}
				else if (isButton(6, vMousePosition))
				{
					m_eCommandType = Command_Mine;
				}
				else if (isButton(7, vMousePosition))
				{
					m_eCommandType = Command_Harvest;
				}
				else if (isButton(8, vMousePosition))
				{
					m_eCommandType = Command_Die;
				}
				else if (isButton(9, vMousePosition))
				{
					m_eCommandType = Command_Boost;
				}
				else if (isButton(10, vMousePosition))
				{
					m_eCommandType = Command_GoToHQWithLumber;
				}
			}
		}
		m_bCommand = true;
	}
	else
	{
		if (m_bCommand) // just released
		{
			// Restart the command display timer
			m_CommandDisplayClock.restart();

			// Do the command
			ListEntity* pSelectedEntities = m_pGM->getSelectedEntities();
			for (ListEntity::iterator i = pSelectedEntities->begin(); i != pSelectedEntities->end(); ++i)
			{
				Entity* pEntity = (Entity*)*i;

				// CharacterController
				m_pCharacterController = pEntity->getComponent<CharacterController>();
				if (m_pCharacterController)
				{
					if (m_eCommandType == Command_Reset)
					{
						m_pTextCommand->setString("Reset");
						MsgManager::getSingleton()->sendMsg(0.f, MSG_Reset, 0, pEntity->GetID(), -1);
						//m_pCharacterController->setAction(kAct_Default);
						//m_pCharacterController->setCondition(kACond_Default);
					}
					else if (m_eCommandType == Command_Kill)
					{
						m_pTextCommand->setString("Kill");
						MsgManager::getSingleton()->sendMsg(0.f, MSG_Kill, 0, pEntity->GetID(), -1);
						//m_pCharacterController->setAction(kAct_Chop);
						//m_pCharacterController->setCondition(kACond_Default);
					}
					else if (m_eCommandType == Command_Stop)
					{
						m_pTextCommand->setString("Stop");
						MsgManager::getSingleton()->sendMsg(0.f, MSG_Stop, 0, pEntity->GetID(), -1);
						//m_pCharacterController->setAction(kAct_Idle);
						//m_pCharacterController->setCondition(kACond_Default);
					}
					else if (m_eCommandType == Command_GoToHQ)
					{
						m_pTextCommand->setString("GoToWithGold");
						MsgManager::getSingleton()->sendMsg(0.f, MSG_GoToWithGold, 0, pEntity->GetID(), -1);
						//m_pCharacterController->setAction(kAct_Walk);
						//m_pCharacterController->setCondition(kACond_Gold);
					}
					else if (m_eCommandType == Command_GoTo)
					{
						m_pTextCommand->setString("GoTo");
						MsgManager::getSingleton()->sendMsg(0.f, MSG_GoTo, 0, pEntity->GetID(), -1);
						//m_pCharacterController->setAction(kAct_Walk);
						//m_pCharacterController->setCondition(kACond_Default);
					}
					else if (m_eCommandType == Command_Build)
					{
						m_pTextCommand->setString("Build");
						MsgManager::getSingleton()->sendMsg(0.f, MSG_Build, 0, pEntity->GetID(), -1);
						//m_pCharacterController->setAction(kAct_Chop);
						//m_pCharacterController->setCondition(kACond_Default);
					}
					else if (m_eCommandType == Command_Mine)
					{
						m_pTextCommand->setString("Mine");
						MsgManager::getSingleton()->sendMsg(0.f, MSG_Mine, 0, pEntity->GetID(), -1);
						//m_pCharacterController->setAction(kAct_Chop);
						//m_pCharacterController->setCondition(kACond_Default);
					}
					else if (m_eCommandType == Command_Harvest)
					{
						m_pTextCommand->setString("Harvest");
						MsgManager::getSingleton()->sendMsg(0.f, MSG_Harvest, 0, pEntity->GetID(), -1);
						//m_pCharacterController->setAction(kAct_Chop);
						//m_pCharacterController->setCondition(kACond_Default);
					}
					else if (m_eCommandType == Command_Die)
					{
						m_pTextCommand->setString("Die");
						MsgManager::getSingleton()->sendMsg(0.f, MSG_Hit, 0, pEntity->GetID(), -1);
						//m_pCharacterController->setAction(kAct_Die);
						//m_pCharacterController->setCondition(kACond_Default);
					}
					else if (m_eCommandType == Command_Boost)
					{
						m_pTextCommand->setString("Boost");
						MsgManager::getSingleton()->sendMsg(0.f, MSG_Boost, 0, pEntity->GetID(), -1);
						//m_pCharacterController->setAction(kAct_Idle);
					}
					else if (m_eCommandType == Command_GoToHQWithLumber)
					{
						m_pTextCommand->setString("GoToWithLumber");
						MsgManager::getSingleton()->sendMsg(0.f, MSG_GoToWithLumber, 0, pEntity->GetID(), -1);
						//m_pCharacterController->setAction(kAct_Walk);
						//m_pCharacterController->setCondition(kACond_Lumber);
					}
					else
					{
						m_pTextCommand->setString("?");
					}
				}
			}

			m_eCommandType = Command_Invalid;
		}
		m_bCommand = false;
	}

	return true;
}

bool AITools::onDraw()
{
	// todo : temporary
	return true;

	// Selection
	if (m_pGM->isMouseButtonPressed(Button::MouseLeft))
	{
		Vector2f vMousePosition = m_pGM->getMousePosition();
		m_pSelectionShape->setPosition(m_vStartSelection.getX(), m_vStartSelection.getY());
		m_pSelectionShape->setSize(vMousePosition.getX() - m_vStartSelection.getX(), vMousePosition.getY() - m_vStartSelection.getY());
		m_pSelectionShape->draw();
	}

	// Diagnostics
	ListEntity* pSelectedEntities = m_pGM->getSelectedEntities();
	for (ListEntity::iterator i = pSelectedEntities->begin(); i != pSelectedEntities->end(); ++i)
	{
		Entity* pEntity = (Entity*)*i;
		Vector2f position = pEntity->getPosition();
		m_pTextDiagnostics->setPosition(position.getX() + 36, position.getY() - 50);
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

		}

		// CharacterController
		m_pCharacterController = pEntity->getComponent<CharacterController>();
		if (m_pCharacterController)
		{
			szDiagnostics += "\nAct�: ";
			szDiagnostics += to_string(m_pCharacterController->getAction());
			szDiagnostics += " Condit�: ";
			szDiagnostics += to_string(m_pCharacterController->getCondition());
			szDiagnostics += " Direct�: ";
			szDiagnostics += to_string(m_pCharacterController->getDirection());
		}

		m_pTextDiagnostics->setString(szDiagnostics);
		m_pTextDiagnostics->draw();

		// Steering
		m_pSteering = pEntity->getComponent<Steering>();
		if (m_pSteering)
		{
			Vector2f start = pEntity->getPosition();

			Entity* pTarget = m_pSteering->getTarget();
			if (pTarget)
			{
				Vector2f end = pTarget->getPosition() + m_pSteering->getTargetOffset();
				m_pTarget->setStartAndEnd(start.getX(), start.getY(), end.getX(), end.getY());
				m_pTarget->draw();
			}
			Vector2f steeringend = start + m_pSteering->getSteeringDirection();
			m_pSteeringLine->setStartAndEnd(start.getX(), start.getY(), steeringend.getX(), steeringend.getY());
			m_pSteeringLine->draw();

			m_pVehicle = pEntity->getComponent<Vehicle>();
			if (m_pVehicle)
			{
				Vector2f forceend = start + m_pVehicle->getLastForce();
				m_pForceLine->setStartAndEnd(start.getX(), start.getY(), forceend.getX(), forceend.getY());
				m_pForceLine->draw();

				Vector2f velocityend = start + m_pVehicle->getVelocity();
				m_pVelocityLine->setStartAndEnd(start.getX(), start.getY(), velocityend.getX(), velocityend.getY());
				m_pVelocityLine->draw();
			}
		}

	}

	// Commands
	if (!pSelectedEntities->empty())
	{
		m_pCommandsSprite->draw();
	}

	// FPS
	m_pTextFPS->draw();

	if (m_CommandDisplayClock.getElapsedTime().asSeconds() < m_fCommandDisplayTime)
	{
		m_pTextCommand->draw();
	}

	/*
	// Grid (slow drawing)
	for (short i = m_iMin; i <= m_iMax; i++)
	{
		for (short j = m_jMin; j <= m_jMax; j++)
		{
			m_pNodeShape->setPosition((float)i*m_nTileWidth, (float)j*m_nTileHeight);
			m_pNodeShape->draw();
		}
	}
	*/
	
	// Grid (fast drawing)
	m_pLineShape->setScale(1.0f, (float)(m_jMax + 1)*m_nTileHeight);
	for (short i = m_iMin; i <= m_iMax; i++)
	{
		m_pLineShape->setPosition((float)i*m_nTileWidth, (float)m_jMin);
		m_pLineShape->draw();
	}
	m_pLineShape->setScale((float)(m_iMax + 1)*m_nTileWidth, 1.f);
	for (short j = m_jMin; j <= m_jMax; j++)
	{
		m_pLineShape->setPosition((float)m_iMin, (float)j*m_nTileHeight);
		m_pLineShape->draw();
	}
	
	// Collision nodes
	for (short i = m_iMin; i <= m_iMax; i++)
	{
		for (short j = m_jMin; j <= m_jMax; j++)
		{
			if (m_pMap->getNode(i, j)->getTileCollisionId() == 9)
			{
				m_pCollisionNodeShape->setPosition((float)i*m_nTileWidth, (float)j*m_nTileHeight);
				m_pCollisionNodeShape->draw();
			}
		}
	}

	// Collisions
	MapStringCollider* pStaticColliders = PhysicsManager::getSingleton()->getStaticColliders();
	DisplayCollider(pStaticColliders);
	MapStringCollider* pDynamicColliders = PhysicsManager::getSingleton()->getDynamicColliders();
	DisplayCollider(pDynamicColliders);

	// Cluster
	short nVariableClusterWidth, nVariableClusterHeigth;
	for (short i = m_iClusterMin; i < m_iClusterMax; i++)
	{
		for (short j = m_jClusterMin; j < m_jClusterMax; j++)
		{
			Cluster* pCluster = m_pMap->getCluster(i, j);
			pCluster->getSize(nVariableClusterWidth, nVariableClusterHeigth);
			m_pClusterShape->setPosition((float)i*m_nClusterWidth*m_nTileWidth, (float)j*m_nClusterHeight*m_nTileHeight);
			m_pClusterShape->setSize((float)nVariableClusterWidth*m_nTileWidth, (float)nVariableClusterHeigth*m_nTileHeight);
			m_pClusterShape->draw();

			// Entrances
			vector<Entrance*>* vEntrances = pCluster->getEntrances();
			for (size_t e = 0; e < vEntrances->size(); e++)
			{
				Entrance* pEntrance = (*vEntrances)[e];
				m_pEntranceShape->setPosition((float)pEntrance->m_pStart->getX()*m_nTileWidth, (float)pEntrance->m_pStart->getY()*m_nTileHeight);
				m_pEntranceShape->draw();
				m_pEntranceShape->setPosition((float)pEntrance->m_pEnd->getX()*m_nTileWidth, (float)pEntrance->m_pEnd->getY()*m_nTileHeight);
				m_pEntranceShape->draw();
			}
		}
	}

	for (short i = m_iClusterMin; i < m_iClusterMax; i++)
	{
		for (short j = m_jClusterMin; j < m_jClusterMax; j++)
		{
			Cluster* pCluster = m_pMap->getCluster(i, j);
			// Transitions
			vector<Transition*>* vTransitions = pCluster->getTransitions();
			for (size_t t = 0; t < vTransitions->size(); t++)
			{
				Transition* pTransition = (*vTransitions)[t];
				m_pTransitionShape->setStartAndEnd(
					(float)(pTransition->m_pStart->getX() + 0.5f)*m_nTileWidth, (float)(pTransition->m_pStart->getY() + 0.5f)*m_nTileWidth,
					(float)(pTransition->m_pEnd->getX() + 0.5f)*m_nTileHeight, (float)(pTransition->m_pEnd->getY() + 0.5f)*m_nTileHeight
				);
				m_pTransitionShape->draw();
			}
			// Edges
			vector<Edge*>* vEdges = pCluster->getEdges();
			for (size_t t = 0; t < vEdges->size(); t++)
			{
				Edge* pEdge = (*vEdges)[t];
				m_pEdgeShape->setStartAndEnd(
					(float)(pEdge->m_pStart->getX() + 0.5f)*m_nTileWidth, (float)(pEdge->m_pStart->getY() + 0.5f)*m_nTileWidth,
					(float)(pEdge->m_pEnd->getX() + 0.5f)*m_nTileHeight, (float)(pEdge->m_pEnd->getY() + 0.5f)*m_nTileHeight
				);
				m_pEdgeShape->draw();
			}
		}
	}

	return true;
}

bool AITools::onQuit()
{
	return true;
}

void AITools::DisplayCollider(MapStringCollider* _pColliders)
{
	for (MapStringCollider::iterator it = _pColliders->begin(); it != _pColliders->end(); ++it)
	{
		Collider* pCollider = (Collider*)(it->second);
		EnumColliderType type = pCollider->getColliderType();
		if (type == Collider_Box)
		{
			BoxCollider* pBoxCollider = (BoxCollider*)pCollider;
			Vector2f position = pBoxCollider->getOrigin();
			Vector2f size = pBoxCollider->getSize();
			m_pBoxColliderShape->setPosition(position.getX(), position.getY());
			m_pBoxColliderShape->setSize(size.getX(), size.getY());
			m_pBoxColliderShape->draw();

		}
		else if (type == Collider_Circle)
		{
			CircleCollider* pCircleCollider = (CircleCollider*)pCollider;
			Vector2f position = pCircleCollider->getWorldCenter();
			float radius = pCircleCollider->getRadius();
			m_pCircleColliderShape->setPosition(position.getX() - radius, position.getY() - radius);
			m_pCircleColliderShape->setRadius(radius);
			m_pCircleColliderShape->draw();
		}
	}
}