/***************************************************/
/* Nom:	MapSearch.h
/* Description: MapSearch
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __MapSearch_H__
#define __MapSearch_H__

#include "AI\Pathfinding\AStarSearch.h"
#include "AI\Pathfinding\MapSearchNode.h"

namespace crea
{
	class CREAENGINE_API VectorVector2f : public vector<Vector2f*> {};
	class CREAENGINE_API MapSearch : public AStarSearch<MapSearchNode>
	{
	public:
		enum SearchState
		{
			SEARCH_STATE_NOT_INITIALISED,
			SEARCH_STATE_SEARCHING,
			SEARCH_STATE_SUCCEEDED,
			SEARCH_STATE_FAILED,
			SEARCH_STATE_OUT_OF_MEMORY,
			SEARCH_STATE_INVALID
		};

		MapSearch();
		~MapSearch();

		bool setStartAndGoal(Vector2f _vStart, Vector2f _vGoal);
		SearchState update();
		bool getSolution(VectorVector2f& _vSolution);
		bool getOpenList(VectorVector2f& _vOpenList);

		// AA*
		Agent* getCurrentAgent() { return m_pAgent; }
		void setCurrentAgent(Agent* _pAgent) { m_pAgent = _pAgent; }

	private:
		SearchState m_uiSearchState;
		Agent* m_pAgent;

	};

}
#endif	// __MapSearch_H__