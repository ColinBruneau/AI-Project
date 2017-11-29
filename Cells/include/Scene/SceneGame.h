/***************************************************/
/* Nom:	SceneGame.h
/* Description: SceneGame
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __SceneGame_H_
#define __SceneGame_H_

#include <list>
#include "Core\Scene.h"
#include "AI\ActionTable.h"
#include "Physics\Collider.h"
#include "Scripts\CellsScriptFactory.h"

#include "FSMPeon.h"
#include "Tools\AITools.h"

using namespace crea;

class SceneGame : public crea::Scene
{
	GameManager*	m_pGM;

	IText* m_pTextFPS;

	Agent* m_pAgent1;
	FSMPeon* m_pFSMPeon1;

	Agent* m_pAgent2;
	FSMPeon* m_pFSMPeon2;

	Clock frameClock;

	Entity* m_pEntity3;

	// AI Tools
	bool m_bUseAITools;
	AITools* m_pAITools;

	// Scripts
	CellsScriptFactory* m_pCellsScriptFactory;

public:
	SceneGame();
	virtual ~SceneGame();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
