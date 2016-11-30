#include "stdafx.h"

#include "Data\TileSet.h"

namespace crea
{
	TileSet::TileSet()
	{
	}

	TileSet::~TileSet()
	{
		VectorTerrain::iterator it = m_Terrains.begin();
		while (it != m_Terrains.end()) {
			delete (*it);
			it = m_Terrains.erase(it);
		}
	}

	float TileSet::getFriction(short nTerrain)
	{
		VectorTerrain::iterator it = m_Terrains.begin();
		while (it != m_Terrains.end()) {
			Terrain* pTerrain = (Terrain*)(*it);
			if (nTerrain == pTerrain->m_nTile)
			{
				return pTerrain->m_fFriction;
			}
			++it;
		}
		return 0.5f; // No friction found, give default 0.5f (not ice, not blocking)
	}
}