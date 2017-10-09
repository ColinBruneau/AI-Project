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
#include "Physics\CharacterController.h"
#include "Input\UserController.h"
#include "Physics\Collider.h"

#include "FSMPeon.h"

using namespace crea;

enum EnumCommandType
{
	Command_Invalid = -1,
	Command_Reset = 0,
	Command_Kill,
	Command_Stop,
	Command_Start,
	Command_Teleport
};

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

	// Selection
	bool m_bSelection;
	Vector2f m_vStartSelection;
	Vector2f m_vEndSelection;

	// Command
	bool m_bCommand;
	EnumCommandType m_eCommandType;

	// Diagnostic
	IText* m_pTextDiagnostics;
	ISprite* m_pPathSprite;

public:
	SceneGame();
	virtual ~SceneGame();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
