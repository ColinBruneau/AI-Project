#include "stdafx.h"

#include "Scripts\FSMPeonGoTo.h"
#include "Scripts\Messages.h"
#include <string.h>


FSMPeonGoTo::FSMPeonGoTo(Vector2f _vTarget) : m_vTarget(_vTarget)
{
	m_pPathNodeShape = (RectangleShape*)m_pGM->getShape("Rectangle", "m_pPathNodeShape");
	Color* pBlueTransparent = m_pGM->getColor("BlueTransparent");
	pBlueTransparent->setValues(0, 0, 255, 125);
	m_pPathNodeShape->setColor(pBlueTransparent);
	m_pPathNodeShape->setSize(10, 10);
	m_pPathNodeShape->setOrigin(5, 5);
	m_pPathNodeShapeOpen = (RectangleShape*)m_pGM->getShape("Rectangle", "m_pPathNodeShapeOpen");
	Color* pGreenTransparent = m_pGM->getColor("GreenTransparent");
	pGreenTransparent->setValues(0, 255, 0, 125);
	m_pPathNodeShapeOpen->setColor(pGreenTransparent);
	m_pPathNodeShapeOpen->setSize(32, 32);
	m_pArrowShape = (ArrowShape*)m_pGM->getShape("Rectangle", "m_pArrowShape");
	Color* pYellowTransparent = m_pGM->getColor("YellowTransparent");
	pYellowTransparent->setValues(255, 255, 0, 125);
	m_pArrowShape->setColor(pYellowTransparent);
	m_pArrowShape->setOutlineColor(pYellowTransparent);
	m_pArrowShape->setSize(32, 32*0.5f);
}

FSMPeonGoTo::~FSMPeonGoTo()
{
	for (short i = 0; i < (short)m_vPath.size(); i++)
	{
		delete m_vPath[i];
	}
	m_vPath.clear();
}

bool FSMPeonGoTo::States(StateMachineEvent _event, Msg* _msg, int _state)
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
			m_pMapSearch = m_pGM->getMapSearch(m_pEntity->getName());
			// Get Agent
			m_pAgent = m_pEntity->getComponent<Agent>();
		OnUpdate
			SetState(STATE_SearchPath);
		/////////////////////////////////////////////////////////////////
		State(STATE_SearchPath)
			OnEnter
			m_pMapSearch->setStartAndGoal(m_pEntity->getPosition(), m_vTarget);
			m_pCharacterController->move(Vector2f(0.f, 0.f));

		OnUpdate
			MapSearch::SearchState s = m_pMapSearch->update(); // 1 iteration per frame!
			m_pMapSearch->getOpenList(m_vOpenList);
			//m_bHasOpenList = true;
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
			m_bHasEdges = false;
			m_pMapSearch->getSolution(m_vPath);
			m_bHasPath = true;
			for (VectorVector2f::iterator it = m_vPath.begin(); it != m_vPath.end(); ++it)
			{
				**it += Vector2f(16.f, 24.f); // Visual offset (top left to center, a bit lower)
			}
			m_pCharacterController->followPath(m_vPath);

		OnUpdate
			if (!m_pCharacterController->isFollowingPath())
			{ 
				SetState(STATE_CompletedPath);
			}

		OnExit
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

bool FSMPeonGoTo::draw()
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
	
	if (m_bHasEdges)
	{
		for (vector<Edge*>::iterator it = m_vEdges.begin(); it != m_vEdges.end(); ++it)
		{
			Edge* p = *it;
			m_pArrowShape->setStartAndEnd((float)p->m_pStart->getX()*32+16, (float)p->m_pStart->getY() * 32 + 16, (float)p->m_pEnd->getX() * 32 + 16, (float)p->m_pEnd->getY() * 32 + 16);
			m_pArrowShape->draw();
		}
	}
	return true;
}