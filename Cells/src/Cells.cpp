/***************************************************/
/* Nom:	Cells
/* Description: Cells est une application de test
/* du module d'IA d�velopp� � Creajeux
/* Il est bas� sur le moteur CreaEngine qui utilise
/* le framework SFML.
/* Auteur: BRUNEAU Colin
/***************************************************/
#include "stdafx.h"
#include "Core\GameManager.h"
#include "Core\SceneManager.h"
#include "Scene\SceneMenu.h"
#include "Scene\SceneGame.h"
#include "Scene\SceneSteering.h"
#include "Scene\SceneFormation.h"
#include "Scene\SceneBehaviorTree.h"


int _tmain(int argc, _TCHAR* argv[])
{
	GameManager* pGM = GameManager::getSingleton();

	pGM->init();

	pGM->setScene(new SceneBehaviorTree());

	pGM->update();

	pGM->quit();

	return 0;
}

