#include "stdafx.h"

#include "AI\Pathfinding\MapSearchManager.h"
#include "Data\Node.h"

namespace crea
{
	MapSearch::MapSearch()
	{
		m_uiSearchState = (SearchState) AStarSearch<MapSearchNode>::SEARCH_STATE_NOT_INITIALISED;
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
			m_pAStarSearch.FreeSolutionNodes();
			bAvailable = true;
		}

		if (bAvailable)
		{
			Map* pMap = MapSearchManager::getSingleton()->getMap();
			Vector2f vStart = pMap->getNodePositionFromPixels(_vStart);
			Vector2f vGoal = pMap->getNodePositionFromPixels(_vGoal);
			MapSearchNode nodeStart((int)vStart.getX(), (int)vStart.getY());
			MapSearchNode nodeEnd((int)vGoal.getX(), (int)vGoal.getY());
			// Set Start and goal states	
			m_pAStarSearch.SetStartAndGoalStates(nodeStart, nodeEnd);
			m_uiSearchState = (SearchState)m_pAStarSearch.SearchStep();
		}

		return bAvailable;
	}

	MapSearch::SearchState MapSearch::update()
	{
		if (m_uiSearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING)
		{
			// Step into search
			m_uiSearchState = (SearchState) m_pAStarSearch.SearchStep();
		}
		return m_uiSearchState;
	}

	bool MapSearch::getSolution(VectorVector2f& _vSolution)
	{
		if (m_uiSearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED)
		{
			Map* pMap = MapSearchManager::getSingleton()->getMap();
			MapSearchNode* node = m_pAStarSearch.GetSolutionStart();
			while (node)
			{
				Vector2f vNode = pMap->getPixelsFromNodePosition(Vector2f((float)node->x, (float)node->y));
				_vSolution.push_back(new Vector2f(vNode));
				node = m_pAStarSearch.GetSolutionNext();
			}
			return true;
		}
		return false;
	}

	MapSearchManager::MapSearchManager()
	{
		m_pMap = nullptr;
	}

	MapSearchManager::~MapSearchManager()
	{
	}	

	MapSearch* MapSearchManager::getMapSearch(string _szName)
	{
		MapStringMapSearch::iterator it = m_MapSearches.find(_szName);
		if (it == m_MapSearches.end())
		{
			MapSearch* pMapSearch = new MapSearch();
			m_MapSearches[_szName] = pMapSearch;
			return pMapSearch;
		}
		else
		{
			return it->second;
		}
	}

}