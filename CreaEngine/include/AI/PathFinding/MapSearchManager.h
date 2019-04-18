/***************************************************/
/* Nom:	MapSearchManager.h
/* Description: MapSearchManager
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __MapSearchManager_H__
#define __MapSearchManager_H__

#include "Core\Singleton.h"
#include "AI\Pathfinding\MapSearch.h"
#include "AI\Pathfinding\MapSearchNode.h"

namespace crea
{
	class CREAENGINE_API MapStringMapSearch : public map<string, MapSearch*> {};

	class CREAENGINE_API MapSearchManager : public Singleton <MapSearchManager>
	{
	public:

		MapSearchManager();
		~MapSearchManager();

		MapSearch* getMapSearch(string _szName);

		// A*
		Map* getCurrentMap() { return m_pCurrentMap; }
		void setCurrentMap(Map* _pCurrentMap) { m_pCurrentMap = _pCurrentMap; }

	private:

		MapStringMapSearch m_MapSearches;
		Map* m_pCurrentMap;
	};

}
#endif	// __MapSearchManager_H__