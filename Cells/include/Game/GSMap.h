/***************************************************/
/* Nom:	GSMap.h
/* Description: GSMap
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __GSMap_H_
#define __GSMap_H_

#include "Core\GameState.h"

using namespace crea;

class GSMap : public GameState
{
	GameManager*	m_pGM;

	// Map
	Entity* m_pEntity3;
	Map* m_pMap;
	MapRenderer* m_pMapRenderer;

public:
	GSMap();
	virtual ~GSMap();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
