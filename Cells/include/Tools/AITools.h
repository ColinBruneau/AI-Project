/***************************************************/
/* Nom:	AITools.h
/* Description: AITools
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __AITools_H_
#define __AITools_H_

#include "Core\Scene.h"
using namespace crea;

enum EnumCommandType
{
	Command_Invalid = -1,
	Command_Reset = 0,
	Command_Kill,
	Command_Stop,
	Command_GoToHQ,
	Command_GoTo,
	Command_Build,
	Command_Mine,
	Command_Harvest,
	Command_Suicide,
	Command_Boost
}; 

class AITools
{
	GameManager*	m_pGM;

	Map* m_pCurrentMap;

	// Selection
	bool m_bSelection;
	Vector2f m_vStartSelection;
	Vector2f m_vEndSelection;
	RectangleShape* m_pSelectionShape;

	// Command
	FloatRect m_rCommandWindow;
	bool m_bCommand;
	EnumCommandType m_eCommandType;
	Sprite* m_pCommandsSprite;

	// Diagnostic
	Text* m_pTextFPS;
	Text* m_pTextCommand;
	Text* m_pTextDiagnostics;
	Clock m_FPSDisplayClock;
	float m_fFPSDisplayTime;
	Clock m_CommandDisplayClock;
	float m_fCommandDisplayTime;

	// Grid
	Map* m_pMap;
	short m_nWidth;
	short m_nHeight;
	short m_nTileWidth;
	short m_nTileHeight;
	RectangleShape* m_pNodeShape;
	RectangleShape* m_pPathShape;

	// Tile index Limits
	int m_iMin;
	int m_iMax;
	int m_jMin;
	int m_jMax;

	bool isButton(int _i, Vector2f& _vMousePosition);

public:
	AITools();
	virtual ~AITools();

	void setCurrentMap(Map* _pMap) { m_pCurrentMap = _pMap; }

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
