#include "stdafx.h"

#include "AI\Pathfinding\ClusterSearchManager.h"

namespace crea
{
	ClusterSearchManager::ClusterSearchManager()
	{
		m_pMap = nullptr;
		m_pCluster = nullptr;
	}

	ClusterSearchManager::~ClusterSearchManager()
	{
		MapStringClusterSearch::iterator it = m_ClusterSearches.begin();
		while (it != m_ClusterSearches.end()) {
			delete (*it).second;
			it = m_ClusterSearches.erase(it);
		}
	}

	ClusterSearch* ClusterSearchManager::getClusterSearch(string _szName)
	{
		MapStringClusterSearch::iterator it = m_ClusterSearches.find(_szName);
		if (it == m_ClusterSearches.end())
		{
			ClusterSearch* pClusterSearch = new ClusterSearch();
			m_ClusterSearches[_szName] = pClusterSearch;
			return pClusterSearch;
		}
		else
		{
			return it->second;
		}
	}

}