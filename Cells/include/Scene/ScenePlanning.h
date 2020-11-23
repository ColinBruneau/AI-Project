/***************************************************/
/* Nom:	ScenePlanning.h
/* Description: ScenePlanning
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __ScenePlanning_H_
#define __ScenePlanning_H_

#include "Core\Scene.h"
#include "Tools\AITools.h"
#include "Scripts\CellsScriptFactory.h"

using namespace crea;

class ScenePlanning : public Scene
{
	GameManager*	m_pGM;
	IntRect m_rWindowRect;

	// MapGoap
	Entity* m_pEntity4;
	Map* m_pMap;
	MapRenderer* m_pMapRenderer;

	// AI Tools
	bool m_bUseAITools;
	AITools* m_pAITools;

	// Scripts
	CellsScriptFactory* m_pCellsScriptFactory;

public:

	ScenePlanning();
	virtual ~ScenePlanning();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
