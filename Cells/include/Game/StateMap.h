/***************************************************/
/* Nom:	StateMap.h
/* Description: StateMap
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __StateMap_H_
#define __StateMap_H_

#include "Core\State.h"

class StateMap : public crea::State
{
	crea::GameManager*	m_pGM;

	// Map
	crea::Entity* m_pEntity3;
	crea::Map* m_pMap;
	crea::MapRenderer* m_pMapRenderer;

public:
	StateMap();
	virtual ~StateMap();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
