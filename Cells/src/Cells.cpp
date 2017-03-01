/***************************************************/
/* Nom:	Cells
/* Description: Cells est une application de test
/* du module d'IA développé à Creajeux
/* Il est basé sur le moteur CreaEngine qui utilise
/* le framework SFML.
/* Auteur: BRUNEAU Colin
/***************************************************/
#include "stdafx.h"
#include "Core\GameManager.h"
#include "Core\SceneManager.h"
#include "Game\GSMenu.h"
#include "Game\GSGame.h"
#include "Game\GSSteering.h"
#include "Game\GSFormation.h"


int _tmain(int argc, _TCHAR* argv[])
{
	GameManager* pGM = GameManager::getSingleton();

	pGM->init();

	pGM->setGameState(new GSGame());

	pGM->update();

	pGM->quit();

	return 0;
}

