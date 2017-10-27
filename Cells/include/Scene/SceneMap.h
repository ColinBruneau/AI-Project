/***************************************************/
/* Nom:	SceneMap.h
/* Description: SceneMap
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __SceneMap_H_
#define __SceneMap_H_

#include "Core\Scene.h"
#include "Tools\AITools.h"

using namespace crea;

class SceneMap : public Scene
{
	GameManager*	m_pGM;

	// Map
	Entity* m_pEntity3;
	Map* m_pMap;
	MapRenderer* m_pMapRenderer;

	// AI Tools
	bool m_bUseAITools;
	AITools* m_pAITools;

public:
	SceneMap();
	virtual ~SceneMap();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
