#include "stdafx.h"

#include "AI\Pathfinding\MapSearchManager.h"
#include "Data\Node.h"

namespace crea
{
	MapSearchManager::MapSearchManager()
	{
		m_pCurrentMap = nullptr;
	}

	MapSearchManager::~MapSearchManager()
	{
		MapStringMapSearch::iterator it = m_MapSearches.begin();
		while (it != m_MapSearches.end()) {
			delete (*it).second;
			it = m_MapSearches.erase(it);
		}
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