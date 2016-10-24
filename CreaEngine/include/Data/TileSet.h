/***************************************************/
/* Nom:	TileSet.h
/* Description: TileSet
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __TileSet_H_
#define __TileSet_H_

#include <vector>

namespace crea
{
	class CREAENGINE_API TileSet
	{

	public:
		short m_nColumns;
		short m_nFirstgid;
		short m_nImageheight;
		short m_nImagewidth;
		short m_nMargin;
		string m_szName;
		short m_nSpacing;
		short m_nTilecount;
		short m_nTileheight;
		short m_nTilewidth;
		string m_szTransparentcolor;
		ISprite* m_pSprite;

		TileSet() {}

		~TileSet() {}
		
	};

} // namespace crea

#endif
