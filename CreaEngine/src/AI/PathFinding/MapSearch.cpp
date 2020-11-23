#include "stdafx.h"

#include "AI\Pathfinding\MapSearch.h"
#include "AI\Pathfinding\MapSearchNode.h"
#include "AI\Pathfinding\MapSearchManager.h"
#include "Data\Node.h"

namespace crea
{
	MapSearch::MapSearch()
	{
		m_uiSearchState = (SearchState)AStarSearch<MapSearchNode>::SEARCH_STATE_NOT_INITIALISED;
	}

	MapSearch::~MapSearch()
	{
	}

	bool MapSearch::setStartAndGoal(Vector2f _vStart, Vector2f _vGoal)
	{
		bool bAvailable = false;
		if (m_uiSearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_NOT_INITIALISED)
		{
			bAvailable = true;
		}
		if (m_uiSearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED)
		{
			FreeSolutionNodes();
			bAvailable = true;
		}
		if (m_uiSearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED)
		{
			bAvailable = true;
		}

		if (bAvailable)
		{
			Map* pMap = MapSearchManager::getSingleton()->getCurrentMap();
			Vector2f vStart = pMap->getNodePositionFromPixels(_vStart);
			Vector2f vGoal = pMap->getNodePositionFromPixels(_vGoal);
			MapSearchNode nodeStart((int)vStart.getX(), (int)vStart.getY());
			MapSearchNode nodeEnd((int)vGoal.getX(), (int)vGoal.getY());
			// Set Start and goal states	
			SetStartAndGoalStates(nodeStart, nodeEnd);
			m_uiSearchState = (SearchState)SearchStep();
		}

		return bAvailable;
	}

	MapSearch::SearchState MapSearch::update()
	{
		if (m_uiSearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING)
		{
			// Step into search
			m_uiSearchState = (SearchState)SearchStep();
		}
		return m_uiSearchState;
	}

	bool MapSearch::getSolution(VectorVector2f& _vSolution)
	{
		if (m_uiSearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED)
		{
			Map* pMap = MapSearchManager::getSingleton()->getCurrentMap();
			MapSearchNode* node = GetSolutionStart();
			while (node)
			{
				Vector2f vNode = pMap->getPixelsFromNodePosition(Vector2f((float)node->x, (float)node->y));
				_vSolution.push_back(new Vector2f(vNode));
				node = GetSolutionNext();
			}
			return true;
		}
		return false;
	}

	bool MapSearch::getOpenList(VectorVector2f& _vOpenList)
	{
		if (m_uiSearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING)
		{
			_vOpenList.clear();
			Map* pMap = MapSearchManager::getSingleton()->getCurrentMap();
			MapSearchNode* node = this->GetOpenListStart();
			while (node)
			{
				Vector2f vNode = pMap->getPixelsFromNodePosition(Vector2f((float)node->x, (float)node->y));
				_vOpenList.push_back(new Vector2f(vNode));
				node = GetOpenListNext();
			}
			return true;
		}
		return false;
	}
}