#include "stdafx.h"
#include "AI\PathFinding\MapSearchNode.h"
#include "AI\PathFinding\MapSearchManager.h"
#include "Data\Map.h"
#include "Data\Node.h"
#include <math.h>

namespace crea
{
	bool MapSearchNode::IsSameState(MapSearchNode &rhs)
	{
		// same state in a search is simply when (x,y) are the same
		return ((x == rhs.x) && (y == rhs.y));
	}

	// Here's the heuristic function that estimates the distance from a Node to the Goal. 
	float MapSearchNode::GoalDistanceEstimate(MapSearchNode &nodeGoal)
	{
		float dx = float(((float)x - (float)nodeGoal.x));
		float dy = float(((float)y - (float)nodeGoal.y));

		//return sqrt((dx*dx) + (dy*dy));	// Pythagore
		return ((dx*dx) + (dy*dy));			// Simple Pythagore
											//return (abs(dx) + abs(dy));		// Manhattan
											//return max(abs(dx), abs(dy));		// Diagonal
	}

	bool MapSearchNode::IsGoal(MapSearchNode &nodeGoal)
	{
		return ((x == nodeGoal.x) && (y == nodeGoal.y));
	}

	// This generates the successors to the given Node. It uses a helper function called
	// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
	// is done for each node internally, so here you just set the state information that
	// is specific to the application
	bool MapSearchNode::GetSuccessors(AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node)
	{
		int parent_x = -1;
		int parent_y = -1;

		if (parent_node)
		{
			parent_x = parent_node->x;
			parent_y = parent_node->y;
		}

		MapSearchNode NewNode;
		Map* pMap = MapSearchManager::getSingleton()->getCurrentMap();
		Node* pParent = pMap->getNode(parent_x, parent_y);
		bool bUseAA = pMap->getUseAA();

		// AA*
		Agent* pAgent = nullptr;
		short nAgentSize = 0;
		short nAgentCapability = 0;
		pAgent = ((MapSearch*)astarsearch)->getCurrentAgent();
		if (pAgent)
		{
			nAgentSize = pAgent->getSize();
			nAgentCapability = pAgent->getCapability();
		}

		// push each possible move except allowing the search to go backwards

		Node* pLeft = pMap->getNode(x - 1, y);
		if (pLeft && (pLeft->getTileCollisionId() == 0)
			&& (!bUseAA || bUseAA && pLeft->getTileClearanceId(nAgentCapability) >= nAgentSize)
			&& (pLeft != pParent))
		{
			NewNode = MapSearchNode(x - 1, y);
			astarsearch->AddSuccessor(NewNode);
		}

		Node* pUp = pMap->getNode(x, y - 1);
		if (pUp && (pUp->getTileCollisionId() == 0)
			&& (!bUseAA || bUseAA && pUp->getTileClearanceId(nAgentCapability) >= nAgentSize)
			&& (pUp != pParent))
		{
			NewNode = MapSearchNode(x, y - 1);
			astarsearch->AddSuccessor(NewNode);
		}

		Node* pRight = pMap->getNode(x + 1, y);
		if (pRight && (pRight->getTileCollisionId() == 0)
			&& (!bUseAA || bUseAA && pRight->getTileClearanceId(nAgentCapability) >= nAgentSize)
			&& (pRight != pParent))
		{
			NewNode = MapSearchNode(x + 1, y);
			astarsearch->AddSuccessor(NewNode);
		}

		Node* pDown = pMap->getNode(x, y + 1);
		if (pDown && (pDown->getTileCollisionId() == 0)
			&& (!bUseAA || bUseAA && pDown->getTileClearanceId(nAgentCapability) >= nAgentSize)
			&& (pDown != pParent))
		{
			NewNode = MapSearchNode(x, y + 1);
			astarsearch->AddSuccessor(NewNode);
		}

		// Diagonals

		if (pUp && pLeft)
		{
			Node* pUpLeft = pMap->getNode(x - 1, y - 1);
			if (pUpLeft && (pUpLeft->getTileCollisionId() == 0)
				&& (!bUseAA || bUseAA && pUpLeft->getTileClearanceId(nAgentCapability) >= nAgentSize)
				&& (pUpLeft != pParent)
				&& (pUp->getTileCollisionId() == 0)
				&& (pLeft->getTileCollisionId() == 0)
				)
			{
				NewNode = MapSearchNode(x - 1, y - 1);
				astarsearch->AddSuccessor(NewNode);
			}
		}

		if (pDown && pRight)
		{
			Node* pDownRight = pMap->getNode(x + 1, y + 1);
			if (pDownRight && (pDownRight->getTileCollisionId() == 0)
				&& (!bUseAA || bUseAA && pDownRight->getTileClearanceId(nAgentCapability) >= nAgentSize)
				&& (pDownRight != pParent)
				&& (pDown->getTileCollisionId() == 0)
				&& (pRight->getTileCollisionId() == 0)
				)
			{
				NewNode = MapSearchNode(x + 1, y + 1);
				astarsearch->AddSuccessor(NewNode);
			}
		}

		if (pDown && pLeft)
		{
			Node* pDownLeft = pMap->getNode(x - 1, y + 1);
			if (pDownLeft && (pDownLeft->getTileCollisionId() == 0)
				&& (!bUseAA || bUseAA && pDownLeft->getTileClearanceId(nAgentCapability) >= nAgentSize)
				&& (pDownLeft != pParent)
				&& (pDown->getTileCollisionId() == 0)
				&& (pLeft->getTileCollisionId() == 0)
				)
			{
				NewNode = MapSearchNode(x - 1, y + 1);
				astarsearch->AddSuccessor(NewNode);
			}
		}

		if (pUp && pRight)
		{
			Node* pUpRight = pMap->getNode(x + 1, y - 1);
			if (pUpRight && (pUpRight->getTileCollisionId() == 0)
				&& (!bUseAA || bUseAA && pUpRight->getTileClearanceId(nAgentCapability) >= nAgentSize)
				&& (pUpRight != pParent)
				&& (pUp->getTileCollisionId() == 0)
				&& (pRight->getTileCollisionId() == 0)
				)
			{
				NewNode = MapSearchNode(x + 1, y - 1);
				astarsearch->AddSuccessor(NewNode);
			}
		}

		return true;
	}

	// given this node, what does it cost to move to successor. 
	float MapSearchNode::GetCost(MapSearchNode &successor)
	{
		// The G cost is 1.4 for diagonal move and 1.0 for horizontal or vertical move
		float fDiagCoef = 1.0f;
		int dx = successor.x - x;
		int dy = successor.y - y;
		if ((dx != 0) && (dy != 0))
		{
			fDiagCoef = 1.4f;
		}

		// And could depend on the friction
		Map* pMap = MapSearchManager::getSingleton()->getCurrentMap();
		float friction = pMap->getFrictionAtPosition(pMap->getPixelsFromNodePosition(Vector2f((float)successor.x, (float)successor.y)));

		return 1000.0f * friction + 100.0f * fDiagCoef;
	}

}