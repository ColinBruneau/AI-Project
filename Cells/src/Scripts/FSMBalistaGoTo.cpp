#include "stdafx.h"

#include "Scripts\FSMBalistaGoTo.h"
#include "Scripts\Messages.h"
#include <string.h>


FSMBalistaGoTo::FSMBalistaGoTo(Vector2f _vTarget) : m_vTarget(_vTarget)
{
	m_pPathNodeShape = new RectangleShape;
	Color* pBlueTransparent = m_pGM->getColor("BlueTransparent");
	pBlueTransparent->setValues(0, 0, 255, 125);
	m_pPathNodeShape->setColor(pBlueTransparent);
	m_pPathNodeShape->setSize(10, 10);
	m_pPathNodeShape->setOrigin(5, 5);

	m_pPathNodeShapeOpen = new RectangleShape;
	Color* pGreenTransparent = m_pGM->getColor("GreenTransparent");
	pGreenTransparent->setValues(0, 255, 0, 125);
	m_pPathNodeShapeOpen->setColor(pGreenTransparent);
	m_pPathNodeShapeOpen->setSize(32, 32);
}

FSMBalistaGoTo::~FSMBalistaGoTo()
{
	for (short i = 0; i < (short)m_vPath.size(); i++)
	{
		delete m_vPath[i];
	}
	m_vPath.clear();

	delete m_pPathNodeShape;
	delete m_pPathNodeShapeOpen;
}

bool FSMBalistaGoTo::States(StateMachineEvent _event, Msg* _msg, int _state)
{
	BeginStateMachine
		//OnMsg(MSG_Teleport)
		//SetState(STATE_CompletedPath);

	/////////////////////////////////////////////////////////////////
	State(STATE_Init)
		OnEnter
			// Get Entity
			m_pEntity = getEntity();
			// Get CharacterController
			m_pCharacterController = m_pEntity->getComponent<CharacterController>();
			// A*
			m_pMapSearch = m_pGM->getMapSearch("FSMBalistaGoTo");
			// Get Agent
			m_pAgent = m_pEntity->getComponent<Agent>();
			// Set current agent for AA*
			m_pMapSearch->setCurrentAgent(m_pAgent);

		OnUpdate
			SetState(STATE_SearchPath);

	/////////////////////////////////////////////////////////////////
	State(STATE_SearchPath)
		OnEnter
			Map* pMap = MapSearchManager::getSingleton()->getCurrentMap();
			// Reduce to a size 1 for start position (middle of upper-left node)
			Vector2f start = m_pEntity->getPosition() - Vector2f(16.f, 16.f);
			// Handle target on a size 1 tile 
			Vector2f goal = m_vTarget;
			Node* pNode = pMap->getNodeAtPosition(goal);
			if (!pNode)
			{
				SetState(STATE_SearchFailed);
			}
			else
			{
				Node* pRight = pMap->getNode(pNode->getX() + 1, pNode->getY());
				Node* pDown = pMap->getNode(pNode->getX(), pNode->getY() + 1);
				if (!pRight || pRight->getTileCollisionId() == 9)
				{
					goal -= Vector2f(32.f, 0.f);
				}
				if (!pDown || pDown->getTileCollisionId() == 9)
				{
					goal -= Vector2f(0.f, 32.f);
				}
				m_pMapSearch->setStartAndGoal(start, goal);
				m_pCharacterController->move(Vector2f(0.f, 0.f));
			}

		OnUpdate
			MapSearch::SearchState s = m_pMapSearch->update();
		m_pMapSearch->getOpenList(m_vOpenList);
		m_bHasOpenList = true;
			if (s == MapSearch::SEARCH_STATE_SUCCEEDED)
			{
				SetState(STATE_FollowPath);
			}
			else if (s == MapSearch::SEARCH_STATE_FAILED)
			{
				SetState(STATE_SearchFailed);
			}

		OnExit

	/////////////////////////////////////////////////////////////////
	State(STATE_FollowPath)
		OnEnter
			m_pMapSearch->getSolution(m_vPath);
			m_bHasPath = true;
			for (VectorVector2f::iterator it = m_vPath.begin(); it != m_vPath.end(); ++it)
			{
				**it += Vector2f(32.f, 32.f); // Visual offset (top left to center)
			}
			m_pCharacterController->followPath(m_vPath);

		OnUpdate
			if (!m_pCharacterController->isFollowingPath())
			{
				SetState(STATE_CompletedPath);
			}

		OnExit
			m_pCharacterController->move(Vector2f(0.f, 0.f));
			m_bHasPath = false;

	/////////////////////////////////////////////////////////////////
	State(STATE_SearchFailed)
		OnEnter


		OnUpdate


		OnExit

		/////////////////////////////////////////////////////////////////
		State(STATE_CompletedPath)
		OnEnter


		OnUpdate


		OnExit
		EndStateMachine
}

bool FSMBalistaGoTo::draw()
{
	if (m_bHasPath)
	{
		for (VectorVector2f::iterator it = m_vPath.begin(); it != m_vPath.end(); ++it)
		{
			Vector2f p = **it;
			m_pPathNodeShape->setPosition((float)p.getX(), (float)p.getY());
			m_pPathNodeShape->draw();
		}
	}
	else if (m_bHasOpenList)
	{
		for (VectorVector2f::iterator it = m_vOpenList.begin(); it != m_vOpenList.end(); ++it)
		{
			Vector2f p = **it;
			m_pPathNodeShapeOpen->setPosition((float)p.getX(), (float)p.getY());
			m_pPathNodeShapeOpen->draw();
		}
		m_bHasOpenList = false;
	}
	return true;
}