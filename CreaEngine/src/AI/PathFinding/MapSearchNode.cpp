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

		// same state in a maze search is simply when (x,y) are the same
		if ((x == rhs.x) &&
			(y == rhs.y))
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	// Here's the heuristic function that estimates the distance from a Node
	// to the Goal. 

	float MapSearchNode::GoalDistanceEstimate(MapSearchNode &nodeGoal)
	{
		float xd = float(((float)x - (float)nodeGoal.x));
		float yd = float(((float)y - (float)nodeGoal.y));

		//return sqrt((xd*xd) + (yd*yd));		// Pythagore
		return ((xd*xd) + (yd*yd));	// Simple Pythagore
		//return (abs(xd) + abs(yd));		// Manhattan
		//return max(abs(xd), abs(yd));		// Diagonal

	}

	bool MapSearchNode::IsGoal(MapSearchNode &nodeGoal)
	{

		if ((x == nodeGoal.x) &&
			(y == nodeGoal.y))
		{
			return true;
		}

		return false;
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
		Map* pMap = MapSearchManager::getSingleton()->getMap();

		// push each possible move except allowing the search to go backwards

		if ((pMap->getNode(x - 1, y)->getTileCollisionId() > -1)
			&& !((parent_x == x - 1) && (parent_y == y))
			)
		{
			NewNode = MapSearchNode(x - 1, y);
			astarsearch->AddSuccessor(NewNode);
		}

		if ((pMap->getNode(x, y - 1)->getTileCollisionId() > -1)
			&& !((parent_x == x) && (parent_y == y - 1))
			)
		{
			NewNode = MapSearchNode(x, y - 1);
			astarsearch->AddSuccessor(NewNode);
		}

		if ((pMap->getNode(x + 1, y)->getTileCollisionId() > -1)
			&& !((parent_x == x + 1) && (parent_y == y))
			)
		{
			NewNode = MapSearchNode(x + 1, y);
			astarsearch->AddSuccessor(NewNode);
		}


		if ((pMap->getNode(x, y + 1)->getTileCollisionId() > -1)
			&& !((parent_x == x) && (parent_y == y + 1))
			)
		{
			NewNode = MapSearchNode(x, y + 1);
			astarsearch->AddSuccessor(NewNode);
		}

		// Diagonals
		if ((pMap->getNode(x - 1, y - 1)->getTileCollisionId() > -1)
			&& !((parent_x == x - 1) && (parent_y == y - 1))
			//&& (pMap->getNode( x-1, y )->getTileCollisionId() > -1)
			//&& (pMap->getNode( x, y-1 )->getTileCollisionId() > -1)
			)
		{
			NewNode = MapSearchNode(x - 1, y - 1);
			astarsearch->AddSuccessor(NewNode);
		}

		if ((pMap->getNode(x + 1, y + 1)->getTileCollisionId() > -1)
			&& !((parent_x == x + 1) && (parent_y == y + 1))
			//&& (pMap->getNode( x+1, y )->getTileCollisionId() > -1)
			//&& (pMap->getNode( x, y+1 )->getTileCollisionId() > -1)
			)
		{
			NewNode = MapSearchNode(x + 1, y + 1);
			astarsearch->AddSuccessor(NewNode);
		}

		if ((pMap->getNode(x - 1, y + 1)->getTileCollisionId() > -1)
			&& !((parent_x == x - 1) && (parent_y == y + 1))
			//&& (pMap->getNode( x, y+1 )->getTileCollisionId() > -1)
			//&& (pMap->getNode( x-1, y )->getTileCollisionId() > -1)
			)
		{
			NewNode = MapSearchNode(x - 1, y + 1);
			astarsearch->AddSuccessor(NewNode);
		}

		if ((pMap->getNode(x + 1, y - 1)->getTileCollisionId() > -1)
			&& !((parent_x == x + 1) && (parent_y == y - 1))
			//&& (pMap->getNode( x+1, y )->getTileCollisionId() > -1)
			//&& (pMap->getNode( x, y-1 )->getTileCollisionId() > -1)
			)
		{
			NewNode = MapSearchNode(x + 1, y - 1);
			astarsearch->AddSuccessor(NewNode);
		}

		return true;
	}

	// given this node, what does it cost to move to successor. 

	float MapSearchNode::GetCost(MapSearchNode &successor)
	{
		// The G cost is 1.4 for diagonal move and 1.0 for horizontal or vertical move
		int dx = successor.x - x;
		int dy = successor.y - y;
		if ((dx != 0) && (dy != 0))
		{
			return 1.4f;
		}
		else if ((dx != 0) && (dy == 0))
		{
			return 1.0f;
		}
		else if ((dx == 0) && (dy != 0))
		{
			return 1.0f;
		}

		return 0.0f;

	}

}