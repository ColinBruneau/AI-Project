/***************************************************/
/* Nom:	SceneSteering.h
/* Description: SceneSteering
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef __SceneSteering_H_
#define __SceneSteering_H_

#include "Core\Scene.h"

using namespace crea;

class SceneSteering : public crea::Scene
{
	GameManager*	m_pGM;

	IText* m_pTextFPS;
	Clock frameClock;

	IText* m_pTextSteeringMode;
	int m_iSteeringMode;

	// Entitites
	int m_iNbEntities;
	vector<Entity*> m_vEntities;
	bool m_bKeyPressedAdd;
	bool m_bKeyPressedSub;

	// Obstacles
	vector<Entity*> m_vObstacles;

	Entity* m_pMouse;

	IntRect m_rWindowRect;

public:
	SceneSteering();
	virtual ~SceneSteering();

	void deleteEntities();
	void createEntities(); 
	void setBehavior();

	virtual bool onInit();
	virtual bool onUpdate();
	virtual bool onDraw();
	virtual bool onQuit();

};

#endif
