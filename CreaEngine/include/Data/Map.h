/***************************************************/
/* Nom:	Map.h
/* Description: Map
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __Map_H_
#define __Map_H_

#include <vector>
#include "TileSet.h"

namespace crea
{
	class Node;

	class CREAENGINE_API Map
	{
		// Name
		string m_szName;

		// Dimensions
		short m_nWidth;
		short m_nHeight;
		short m_nTileWidth;
		short m_nTileHeight;

		// Tilesets
		vector<TileSet*> m_TileSet;

		// Nodes
		vector<vector<Node*>> m_Grid;
		bool m_bIsGrid8;

		// Draw modes
		bool m_bDisplayCollision;

	public:

		Map();

		~Map();

		bool loadFromFileJSON(string& _filename);

		inline void setName(string& _szName) { m_szName = _szName; }

		void setSize(short _nWidth, short _nHeight);

		void setNode(short _i, short _j, Node* _pNode) { m_Grid[_i][_j] = _pNode; }

		Node* getNode(short _i, short _j) { return m_Grid[_i][_j]; }

		TileSet* getTileSet(short _gid);

		void setDisplayCollision(bool _b)	{ m_bDisplayCollision = _b;  }

		bool getDisplayCollision()			{ return m_bDisplayCollision; }


		bool update();

		bool draw();

		void clear();
	};

} // namespace crea

#endif
